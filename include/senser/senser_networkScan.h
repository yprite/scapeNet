#ifndef _NETWORKSCAN
#define _NETWORKSCAN
 
#include <pcap.h> 
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include <netinet/ip.h>
#include <netinet/tcp.h>

#include "senser_protocol.h"

#define MAXBYTES2CAPTURE 2048

//struct senser_nodeStatus_get();		//네트워크의 노드상태 확인
//struct senser_nodeInfo_get(nodeIp);	//node의 열린포트, 트레픽 정보 확인

typedef struct NodeInfo {
	int status;	//상태
	int openPorts[20]; //열린포트
	int traffics_up; //traffic 양
	int traffics_down; //traffic 양
} NodeInfo;

typedef struct NodeStatus {
	NodeInfo node[255];
} NodeStatus;

typedef struct grub_args {
	pcap_t *p_descr;
	NodeStatus *p_node_status;
	unsigned char source_ip[4];
} grub_args;

void *networkScan(void *);
void send_arp_packet(pcap_t *, device_info);
unsigned char* make_arp_packet(device_info, u_char );
int get_device_info(device_info *);
void print_packet(const unsigned char *);
void *receiver(void *);
int check_reply_packet(const unsigned char *, struct pcap_pkthdr *, unsigned char *, NodeStatus *);
void confirmNodeTraffic(const unsigned char *packet, struct pcap_pkthdr *pkthdr, unsigned char *source_ip, NodeStatus *p_node_statu);
#endif
