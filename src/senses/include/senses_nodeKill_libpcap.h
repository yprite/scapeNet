/**
 * Senses Node Kill Header
 * @author Kwon HoeGeun
 */
#ifndef _NODEKILL
#define _NODEKILL

#include <pcap.h> 
#include <string.h>
#include <unistd.h>

#include "senses_protocol_libpcap.h"

/** 
 * Kill Node를 선택하는 구조체
 */
typedef struct killnode_list {
	u_char target_ip[255];
} killnode_list;

/** 
 * Networkscan 쓰레드로 넘기는 매개변수 구조체 
 */
typedef struct network_grub_args {
	killnode_list k_list;
	u_char g_ip;
} network_grub_args;

/** 
 * sendKill 쓰레드로 넘기는 매개변수 구조체 
 */
typedef struct sendkill_grub_args {
	pcap_t *descr;
	device_info *gate_info;
	network_grub_args *n_args;
} sendkill_grub_args;

void *send_kill_packet(void *);
unsigned char* make_kill_packet(device_info , u_char , u_char );
int gateway_get(const unsigned char *, u_char , device_info *);

#endif
