/*
 * packetif - 'packet' network interface for lwIP
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (C) 2013 Tom Zanussi <tom.zanussi@linux.intel.com>
 */

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#include "lwip/opt.h"

#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "netif/etharp.h"
#include "netif/ppp_oe.h"

#include "packetdump.h"

#define IFNAME0 'p'
#define IFNAME1 'a'

#define BUF_SIZ		1518

struct packetif {
	char *eth_dev;
	int sockfd;
};

/* Forward declarations. */
static void ethernetif_input(struct netif *netif);

/**
 * Initialize the 'hardware'.  For us, the 'hardware' is a raw socket.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static int
low_level_init(struct netif *netif)
{
	struct packetif *packetif = netif->state;
	struct ifreq if_mac;
	int sockopt;

	/* Open RAW socket to send on */
	if ((packetif->sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
		perror("socket");
		return ERR_IF;
	}

	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, packetif->eth_dev, IFNAMSIZ-1);
	if (ioctl(packetif->sockfd, SIOCGIFHWADDR, &if_mac) < 0) {
		perror("SIOCGIFHWADDR");
		return ERR_IF;
	}

	/* set MAC hardware address length */
	netif->hwaddr_len = ETHARP_HWADDR_LEN;

	/* set MAC hardware address */
	netif->hwaddr[0] = ((u8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
	netif->hwaddr[1] = ((u8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
	netif->hwaddr[2] = ((u8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
	netif->hwaddr[3] = ((u8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
	netif->hwaddr[4] = ((u8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
	netif->hwaddr[5] = ((u8_t *)&if_mac.ifr_hwaddr.sa_data)[5];

	printf("low_level_init: hwaddr[0] %x\n", netif->hwaddr[0]);
	printf("low_level_init: hwaddr[1] %x\n", netif->hwaddr[1]);
	printf("low_level_init: hwaddr[2] %x\n", netif->hwaddr[2]);
	printf("low_level_init: hwaddr[3] %x\n", netif->hwaddr[3]);
	printf("low_level_init: hwaddr[4] %x\n", netif->hwaddr[4]);
	printf("low_level_init: hwaddr[5] %x\n", netif->hwaddr[5]);

	/* maximum transfer unit */
	netif->mtu = 1500;

	/* device capabilities */
	/* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

	/* Allow the socket to be reused - in case connection is closed prematurely */
	if (setsockopt(packetif->sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
		perror("setsockopt");
		close(packetif->sockfd);
		return ERR_IF;
	}

	/* Bind to device */
	if (setsockopt(packetif->sockfd, SOL_SOCKET, SO_BINDTODEVICE, packetif->eth_dev, IFNAMSIZ-1) == -1)	{
		perror("SO_BINDTODEVICE");
		close(packetif->sockfd);
		return ERR_IF;
	}

	return ERR_OK;
}

/**
 * Transmit the packet. The packet is contained in the pbuf that is
 * passed to the function. This pbuf might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	struct packetif *packetif = netif->state;
	struct pbuf *q;
	uint8_t buf[BUF_SIZ];
	unsigned char *bufptr;
	int sent;

	struct sockaddr_ll socket_address;
	struct ifreq if_idx;
	struct eth_hdr *ethhdr;

	ethhdr = (struct eth_hdr *)p->payload;
	fprintf(stderr, "low_level_output, ethhdr->dest: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", ethhdr->dest.addr[0] , ethhdr->dest.addr[1] , ethhdr->dest.addr[2] , ethhdr->dest.addr[3] , ethhdr->dest.addr[4] , ethhdr->dest.addr[5] );

#if ETH_PAD_SIZE
	pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

	bufptr = &buf[0];

	for(q = p; q != NULL; q = q->next) {
		/* Send the data from the pbuf to the interface, one pbuf at a
		   time. The size of the data in each pbuf is kept in the ->len
		   variable. */
		memcpy(bufptr, q->payload, q->len);
		bufptr += q->len;
	}

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, packetif->eth_dev, IFNAMSIZ-1);
	if (ioctl(packetif->sockfd, SIOCGIFINDEX, &if_idx) < 0)
		perror("SIOCGIFINDEX");

	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;
	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;
	/* Destination MAC */
	socket_address.sll_addr[0] = ethhdr->dest.addr[0];
	socket_address.sll_addr[1] = ethhdr->dest.addr[1];
	socket_address.sll_addr[2] = ethhdr->dest.addr[2];
	socket_address.sll_addr[3] = ethhdr->dest.addr[3];
	socket_address.sll_addr[4] = ethhdr->dest.addr[4];
	socket_address.sll_addr[5] = ethhdr->dest.addr[5];

	/* send the packet */
	if (sendto(packetif->sockfd, buf, p->tot_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0) {
		perror("packetif: sendto");
		return ERR_IF;
	}

#if ETH_PAD_SIZE
	pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

	LINK_STATS_INC(link.xmit);

	return ERR_OK;
}

/**
 * Allocate a pbuf and transfer the bytes of the incoming packet from
 * the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *low_level_input(struct netif *netif)
{
	struct packetif *packetif = netif->state;
	struct pbuf *p, *q;
	uint8_t buf[BUF_SIZ];
	unsigned char *bufptr;
	u16_t len;

	/* Obtain the size of the packet and put it into the "len"
	   variable. */
	len = recvfrom(packetif->sockfd, buf, BUF_SIZ, 0, NULL, NULL);

	dump_packet(buf, len);

#if ETH_PAD_SIZE
	len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

	/* We allocate a pbuf chain of pbufs from the pool. */
	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

	if (p != NULL) {
#if ETH_PAD_SIZE
		pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif
		/* We iterate over the pbuf chain until we have read the entire
		   packet into the pbuf. */
		bufptr = &buf[0];
		for(q = p; q != NULL; q = q->next) {
			/* Read enough bytes to fill this pbuf in the chain. The
			   available data in the pbuf is given by the q->len
			   variable. */
			/* read data into(q->payload, q->len); */
			memcpy(q->payload, bufptr, q->len);
			bufptr += q->len;
		}
		/* acknowledge that packet has been read(); */
#if ETH_PAD_SIZE
		pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
		LINK_STATS_INC(link.recv);
	} else {
		printf("Could not allocate pbufs\n");
		LINK_STATS_INC(link.memerr);
		LINK_STATS_INC(link.drop);
	}

	return p;
}

/**
 * Called when a packet is ready to be read from the interface. It
 * uses the function low_level_input() that handles the actual
 * reception of bytes from the network interface. Then the type of the
 * received packet is determined and the appropriate input function is
 * called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
static void
packetif_input(struct netif *netif)
{
	struct eth_hdr *ethhdr;
	struct pbuf *p;

	/* move received packet into a new pbuf */
	p = low_level_input(netif);
	/* no packet could be read, silently ignore this */
	if (p == NULL) return;
	/* points to packet payload, which starts with an Ethernet header */
	ethhdr = p->payload;

	switch (htons(ethhdr->type)) {
		/* IP or ARP packet? */
	case ETHTYPE_IP:
	case ETHTYPE_IPV6:
	case ETHTYPE_ARP:
#if PPPOE_SUPPORT
		/* PPPoE packet? */
	case ETHTYPE_PPPOEDISC:
	case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
		/* full packet send to tcpip_thread to process */
		if (netif->input(p, netif)!=ERR_OK){
			LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
			pbuf_free(p);
			p = NULL;
		}
		break;

	default:
		pbuf_free(p);
		p = NULL;
		break;
	}
}

/**
 * Called at the beginning of the program to set up the network
 * interface. It calls the function low_level_init() to do the actual
 * setup of the hardware.
 *
 * This function is passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t packetif_init(struct netif *netif)
{
	struct packetif *packetif;

	LWIP_ASSERT("netif != NULL", (netif != NULL));

	packetif = mem_malloc(sizeof(struct packetif));
	if (packetif == NULL) {
		LWIP_DEBUGF(NETIF_DEBUG, ("packetif_init: out of memory\n"));
		return ERR_MEM;
	}

	packetif->eth_dev = strdup(netif->state); // TODO: free this

#if LWIP_NETIF_HOSTNAME
	/* Initialize interface hostname */
	netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

	netif->state = packetif;
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = etharp_output;
#if LWIP_IPV6
	netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
	netif->linkoutput = low_level_output;

	/* initialize the hardware */
	return low_level_init(netif);
}

/**
 * Wait for packets from the 'hardware'.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return the return val from select
 */
int packetif_select(struct netif *netif)
{
	fd_set fdset;
	int ret;
	struct timeval tv;
	struct packetif *packetif;

	packetif = netif->state;

	tv.tv_sec = 0;
	tv.tv_usec = 0; /* usec_to; */

	FD_ZERO(&fdset);
	FD_SET(packetif->sockfd, &fdset);

	ret = select(packetif->sockfd + 1, &fdset, NULL, NULL, &tv);
	if (ret > 0) {
		packetif_input(netif);
	}
	return ret;
}

