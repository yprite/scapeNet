/**
 * Senses networkScan Header File
 * @author Kwon HoeGeun
 */
#ifndef _NETWORKSCAN
#define _NETWORKSCAN
 
#include <stdlib.h>
#include <string.h>

#include <pcap.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/epoll.h>
// #include <sys/stat.h>
// #include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "senses_protocol_netfilter.h"
#include "senses_nodeKill_netfilter.h"

#define MAXBYTES2CAPTURE 2048

/** 
 * 확인하는 노드들의 정보를 저장하는 구조체
 */
typedef struct NodeInfo {
	int status;	//상태
	int openPorts[20]; //열린포트
	int traffics_up; //traffic 양
	int traffics_down; //traffic 양
} NodeInfo;

typedef struct NodeStatus {
	NodeInfo node[255];
} NodeStatus;

/*typedef struct killnode_list {
	u_char target_ip[255];
} killnode_list;

typedef struct network_grub_args {
	killnode_list k_list;
	u_char g_ip;
} network_grub_args;*/

/** 
 * receiver 쓰레드 함수로 넘기는 매개변수 구조체
 */
typedef struct receiver_grub_args {
	pcap_t *p_descr;
	NodeStatus *p_node_status;
	unsigned char source_ip[4];
} receiver_grub_args;

void *networkScan(void *);
void send_arp_packet(pcap_t *, device_info);
unsigned char* make_arp_packet(device_info, u_char );

int get_device_info(device_info *);
void print_packet(const unsigned char *);

#endif
