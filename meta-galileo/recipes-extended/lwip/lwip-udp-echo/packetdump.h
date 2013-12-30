#ifndef _PACKETDUMP_H_
#define _PACKETDUMP_H_

extern void dump_packet(unsigned char* buffer, int size);
extern void dump_start(char *logfile_name);
extern void dump_stop(void);

#endif /* _PACKETDUMP_H_ */
