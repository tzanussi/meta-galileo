#ifndef __PACKETIF_H__
#define __PACKETIF_H__

#include "lwip/netif.h"

err_t packetif_init(struct netif *netif);
int packetif_select(struct netif *netif);

#endif /* __PACKETIF_H__ */
