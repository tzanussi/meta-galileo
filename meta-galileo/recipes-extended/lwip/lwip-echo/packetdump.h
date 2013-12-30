#ifndef __PACKETDUMP_H__
#define __PACKETDUMP_H__

extern void dump_packet(unsigned char* buffer, int size);
extern void dump_start(char *logfile_name);
extern void dump_stop(void);

#endif /* __PACKETDUMP_H__ */
