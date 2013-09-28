#ifndef _PROTOCOL
#define _PROTOCOL

#include <stdlib.h>

#define DEVICENAME "eth0"

/* ARP Header, (assuming Ethernet+IPv4)            */ 
#define ARP_REQUEST 1   /* ARP Request             */ 
#define ARP_REPLY 2     /* ARP Reply               */

typedef struct etherhdr {
	unsigned char h_dest[6];
	unsigned char h_source[6];
	unsigned short h_proto;
} etherhdr_t;

typedef struct arphdr { 
	u_int16_t htype;    /* Hardware Type           */ 
	u_int16_t ptype;    /* Protocol Type           */ 
	u_char hlen;        /* Hardware Address Length */ 
	u_char plen;        /* Protocol Address Length */ 
	u_int16_t oper;     /* Operation Code          */ 
	u_char sha[6];      /* Sender hardware address */ 
	u_char spa[4];      /* Sender IP address       */ 
	u_char tha[6];      /* Target hardware address */ 
	u_char tpa[4];      /* Target IP address       */ 
}arphdr_t;

typedef struct device_info {
	unsigned char macaddr[6];
	unsigned char ipaddr[4];
} device_info;

typedef struct ipv4hdr{
	union{
		#if __BYTE_ORDER == __LITTLE_ENDIAN
		     unsigned int ihl:4;
		     unsigned int version:4;
		 #elif __BYTE_ORDER == __BIG_ENDIAN
		     unsigned int version:4;
		     unsigned int ihl:4;
		 #else
		 # error "Please fix <bits/endian.h>"
		 #endif
		     u_int8_t tos;
		     u_int16_t tot_len;
		     u_int16_t id;
		     u_int16_t frag_off;
		     u_int8_t ttl;
		     u_int8_t protocol;
		     u_int16_t check;
		     u_int32_t saddr;
		     u_int32_t daddr;
		     /*The options start here. */	
	}
	char ipHeader[20];
}ipv4hdr_t


typedef struct tcphdr{	
	union{
	     u_int16_t sport;     /* source port */
	     u_int16_t dport;     /* destination port */
	     tcp_seq seq;     /* sequence number */
	     tcp_seq ack;     /* acknowledgement number */
	 #  if __BYTE_ORDER == __LITTLE_ENDIAN
	     u_int8_t x2:4;       /* (unused) */
	     u_int8_t off:4;      /* data offset */
	     struct flags{
	     	union{
			     u_int16_t res1:4;
			     u_int16_t doff:4;
			     u_int16_t fin:1;
			     u_int16_t syn:1;
			     u_int16_t rst:1;
			     u_int16_t psh:1;
			     u_int16_t ack:1;
			     u_int16_t urg:1;
			     u_int16_t res2:2;
	     	}
	     	u_int8_t flags;
	     }
	 #  endif
	 #  if __BYTE_ORDER == __BIG_ENDIAN
	    u_int8_t off:4;      /* data offset */
	     u_int8_t x2:4;       /* (unused) */
	     struct flags{
	     	union{
			     u_int16_t doff:4;
			     u_int16_t res1:4;
			     u_int16_t res2:2;
			     u_int16_t urg:1;
			     u_int16_t ack:1;
			     u_int16_t psh:1;
			     u_int16_t rst:1;
			     u_int16_t syn:1;
			     u_int16_t fin:1;
	     	}
	     	u_int8_t flags;
	     }
	 #  endif
	    u_int16_t win;       /* window */
	    u_int16_t sum;       /* checksum */
	    u_int16_t urp;       /* urgent pointer */
	}
	char tcpHeader[20];
}tcphdr_t

#endif
