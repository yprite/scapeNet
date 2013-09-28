/* Simple ARP Sniffer.                                                   */ 
/* Author: Luis Martin Garcia. luis.martingarcia [.at.] gmail [d0t] com  */
/* To compile: gcc arpsniffer.c -o arpsniff -lpcap                       */
/* Run as root!                                                          */ 
/*                                                                       */
/* This code is distributed under the GPL License. For more info check:  */
/* http://www.gnu.org/copyleft/gpl.html                                  */

#include <pcap.h> 
#include <stdlib.h> 
#include <string.h>
#include <netinet/ip.h>
// #include <netinet/tcp.h>


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

typedef struct tcphdr{	
	union{
	     u_int16_t sport;     /* source port */
	     u_int16_t dport;     /* destination port */
	     u_int32_t seq;     /* sequence number */
	     u_int32_t ack;     /* acknowledgement number */
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
	     	};
	     	u_int8_t flags;
	     };
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
	     	};
	     	u_int8_t flags;
	     };
	 #  endif
	    u_int16_t win;       /* window */
	    u_int16_t sum;       /* checksum */
	    u_int16_t urp;       /* urgent pointer */
	};
	char tcpHeader[20];
}tcphdr_t;

#define MAXBYTES2CAPTURE 2048 

void print_packet(const unsigned char *packet, struct pcap_pkthdr pkthdr);
void reply_packet(const unsigned char *packet, struct pcap_pkthdr pkthdr);
unsigned char* make_arp_packet(u_char sour_last_addr, u_char dest_last_addr);
void send_arp_packet(pcap_t *descr, const unsigned char *pack);

int main(int argc, char *argv[]){
	bpf_u_int32 netaddr=0, mask=0;    /* To Store network address and netmask   */ 
	struct bpf_program filter;        /* Place to store the BPF filter program  */ 
	char errbuf[PCAP_ERRBUF_SIZE];    /* Error buffer                           */ 
	pcap_t *descr = NULL;             /* Network interface handler              */ 
	struct pcap_pkthdr *pkthdr;        /* Packet information (timestamp,size...) */ 
	struct pcap_pkthdr pack_data;
	const unsigned char *packet=NULL; /* Received raw data                      */

	int menu = -1;			/*main에서 필요로 하는것.*/
	int sour = 0;
	int dest = 0;

	pkthdr = &pack_data;
	memset(errbuf,0,PCAP_ERRBUF_SIZE); 

	if (argc != 2){ 
		printf("USAGE: arpsniffer <interface>\n"); 
		exit(1); 
	} 
	/* Open network device for packet capture */ 
	if ((descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,  512, errbuf))==NULL){
		fprintf(stderr, "1ERROR: %s\n", errbuf);
		exit(1);
	}

	/* Look up info from the capture device. */ 
	if( pcap_lookupnet( argv[1] , &netaddr, &mask, errbuf) == -1){
		fprintf(stderr, "2ERROR: %s\n", errbuf);
		exit(1);
	}

	/* Compiles the filter expression into a BPF filter program */ 
	if ( pcap_compile(descr, &filter, "ip", 1, mask) == -1){
		fprintf(stderr, "3ERROR: %s\n", pcap_geterr(descr) );
		exit(1);
	}

	/* Load the filter program into the packet capture device. */ 
	if (pcap_setfilter(descr,&filter) == -1){
		fprintf(stderr, "4ERROR: %s\n", pcap_geterr(descr) );
		exit(1);
	}

	puts("broadcast     : 0");
	puts("SendPacket    : 1");
	puts("sniffer ALL   : 2");
	puts("sniffer Reply : 3");

	// scanf("%d", &menu);

	switch(2) {
		int index;
		case 0 :
			printf("sour_last_addr : ");
			scanf("%d", &sour);
			
			for(index=1; index<255; index++) {
				packet = make_arp_packet(sour, index);
				pcap_sendpacket(descr, packet, 42);
				usleep(50000);
			}
		break;

		case 1 :
			printf("sour_last_addr : ");
			scanf("%d", &sour);
			printf("dest_last_addr : ");
			scanf("%d", &dest);
			
			packet = make_arp_packet(sour, dest);
			send_arp_packet(descr, packet);
		break;

		case 2 :
			while(1){

				if (pcap_next_ex(descr,&pkthdr,&packet) != 1){
					continue;
				}
				print_packet(packet,*pkthdr);
			}
		break;

		case 3 :
			while(1){
				if (pcap_next_ex(descr,&pkthdr,&packet) != 1){
					continue;
				}
				reply_packet(packet,*pkthdr);
			}
		break;

		defalut :
			puts("menu checking!!!");
	}


	/*while(1){
		if ( (packet = pcap_next(descr,&pkthdr)) == NULL){
			continue;
		}


		print_packt(packet,pkthdr);
		break;
	}*/
	/*while(1) {
		pcap_sendpacket(descr, packet, pkthdr.len);
	}*/

	// send_arp_packet(descr);

	return 0; 

}


void print_packet(const unsigned char *packet, struct pcap_pkthdr pkthdr)
{
	// #if 0
	etherhdr_t *ether = (etherhdr_t*)(packet);
	struct ip *iphdr = (struct ip*)(packet+14);
	struct tcphdr *tcp; 

	// arphdr_t *arpheader = (struct arphdr *)(packet+14); /* Point to the ARP header */

	u_int n_ip_temp;
	u_char *p_c_ip;
	unsigned char c_src_ip[4] = {0,};
	unsigned char c_dst_ip[4] = {0,};
	int ippkt_size = iphdr->ip_hl * 4;
	int i=0;
	
	tcp = (struct tcphdr*)(packet+ippkt_size + 14);
	

	n_ip_temp = *((unsigned int*)(&(iphdr->ip_src)));		//형번환.
	p_c_ip = (u_char*)(&n_ip_temp);
	memcpy(&c_src_ip, p_c_ip, 4);

	n_ip_temp = *((unsigned int*)(&(iphdr->ip_dst)));		//형번환.
	p_c_ip = (u_char*)(&n_ip_temp);
	memcpy(&c_dst_ip, p_c_ip, 4);


	if(c_src_ip[3] == 157 || c_src_ip[3] == 54)
		return;



	/*if( ((u_char*)(&n_ip_temp))[3] == 54 || ((u_char*)(&n_ip_temp))[3] == 53 )		//test
		return;*/

	puts("\n------Ethernet Headeer--------------------");
	printf("source= ");
	for(i=0; i<6;i++)
		printf("%02X:", ether->h_source[i]);

	printf("\ndest= ");
	for(i=0; i<6;i++)
		printf("%02X:", ether->h_dest[i]);

	printf("\nproto = %04x\n", ntohs(ether->h_proto));
	puts("------ip Header--------------");

	printf("IP Ver: %x\n", (iphdr->ip_v));
	printf("IP IHL: %x\n", (iphdr->ip_hl));
	printf("IP Tn_ip_temp: %i\n", iphdr->ip_ttl);
	printf("IP Len: %d\n", ntohs(iphdr->ip_len));
	printf("IP off set: %04x\n", ntohs(iphdr->ip_off));
	
	// for(i=0; i<4; i++) {
	// 	printf("IP SRC: %d\n", (unsigned char*)(&(iphdr->ip_src))+i);
	// }
	// printf("%15s\n", inet_ntoa(iphdr->ip_src));
	// printf("%x\n", iphdr->ip_src);

	


	for(i=0; i<4; i++) {
		printf("%d ", c_src_ip[i]);
		// printf("%d ", *((u_char*)(&n_ip_temp)+i) );
	}
	puts("");

	for(i=0; i<4; i++) {
		printf("%d ", c_dst_ip[i]);
		// printf("%d ", *((u_char*)(&n_ip_temp)+i) );
	}
	puts("");
	
	puts("------tcp Header--------------");
	printf("size = %d\n", ippkt_size);

	printf("tcp source port: %d\n",ntohs(tcp->sport));
	printf("tcp dest port: %d\n", ntohs(tcp->sport));







	// puts("------arp Header--------------");

	// printf("Received Packet Size: %d bytes\n", pkthdr.len); 
	// printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ? "Ethernet" : "Unknown"); 
	// printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ? "IPv4" : "Unknown"); 
	// printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST)? "ARP Request" : "ARP Reply");

	// /*printf("Hardware type: %04x\n", ntohs(arpheader->htype));
	// printf("Protocol type: %04x\n", ntohs(arpheader->ptype));
	// printf("Operation: %04x\n", ntohs(arpheader->oper));*/
	// printf("hlen: %02x\n", arpheader->hlen);
	// printf("plen: %02x\n", arpheader->plen);

	// /* If is Ethernet and IPv4, print packet contents */ 
	// if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x0800){ 
	// 	printf("Sender MAC: "); 
			
	// 	for(i=0; i<6;i++)
	// 		printf("%02X:", arpheader->sha[i]); 

	// 	printf("\nSender IP: "); 

	// 	for(i=0; i<4;i++)
	// 		printf("%d.", arpheader->spa[i]); 

	// 	printf("\nTarget MAC: "); 

	// 	for(i=0; i<6;i++)
	// 		printf("%02X:", arpheader->tha[i]); 

	// 	printf("\nTarget IP: "); 

	// 	for(i=0; i<4; i++)
	// 		printf("%d.", arpheader->tpa[i]); 

	// 	printf("\n"); 
	// } 
// #endif
}


unsigned char* make_arp_packet(u_char sour_last_addr, u_char dest_last_addr)
{
	static unsigned char pack_data[42];
	etherhdr_t et_hdr;
	arphdr_t arp_hdr;

	/*ethernet*/
	et_hdr.h_source[0] = 0xb8;//rasberry PI = b8:27:eb:f0:29:7e
	et_hdr.h_source[1] = 0x27;
	et_hdr.h_source[2] = 0xeb;
	et_hdr.h_source[3] = 0xf0;
	et_hdr.h_source[4] = 0x29;
	et_hdr.h_source[5] = 0x7e;
	et_hdr.h_dest[0] = 0xff;
	et_hdr.h_dest[1] = 0xff;
	et_hdr.h_dest[2] = 0xff;
	et_hdr.h_dest[3] = 0xff;
	et_hdr.h_dest[4] = 0xff;
	et_hdr.h_dest[5] = 0xff;
	et_hdr.h_proto = htons(0x0806);
	
	/*arp*/
	arp_hdr.htype = htons(0x0001);
	arp_hdr.ptype = htons(0x0800);
	arp_hdr.oper = htons(ARP_REQUEST);
	arp_hdr.hlen = 0x06;
	arp_hdr.plen = 0x04;

	arp_hdr.sha[0] = 0xb8;
	arp_hdr.sha[1] = 0x27;
	arp_hdr.sha[2] = 0xeb;
	arp_hdr.sha[3] = 0xf0;
	arp_hdr.sha[4] = 0x29;
	arp_hdr.sha[5] = 0x7e;
	arp_hdr.spa[0] = 210;
	arp_hdr.spa[1] = 118;
	arp_hdr.spa[2] = 34;
	arp_hdr.spa[3] = sour_last_addr;

	arp_hdr.tha[0] = 0x00;
	arp_hdr.tha[1] = 0x00;
	arp_hdr.tha[2] = 0x00;
	arp_hdr.tha[3] = 0x00;
	arp_hdr.tha[4] = 0x00;
	arp_hdr.tha[5] = 0x00;
	arp_hdr.tpa[0] = 210;
	arp_hdr.tpa[1] = 118;
	arp_hdr.tpa[2] = 34;
	arp_hdr.tpa[3] = dest_last_addr;

	memset(pack_data, 0, sizeof(pack_data));
	memcpy(pack_data, &et_hdr, 14);
	memcpy(pack_data+14, &arp_hdr, 28);

	return pack_data;
}

void send_arp_packet(pcap_t *descr, const unsigned char *pack)
{
	while(1){
		pcap_sendpacket(descr, pack, 42);
		usleep(50000);
	}
}

void reply_packet(const unsigned char *packet, struct pcap_pkthdr pkthdr)
{
	etherhdr_t *ether = (etherhdr_t*)(packet);
	arphdr_t *arpheader = (struct arphdr *)(packet+14); /* Point to the ARP header */
	int i=0;

	if(ntohs(arpheader->oper) == ARP_REQUEST)
		return ;

	puts("\n------Ethernet Headeer--------------------");
	printf("source= ");
	for(i=0; i<6;i++)
		printf("%02X:", ether->h_source[i]);

	printf("\ndest= ");
	for(i=0; i<6;i++)
		printf("%02X:", ether->h_dest[i]);

	printf("\nproto = %04x\n", ntohs(ether->h_proto));
	puts("------arp Header--------------");

	printf("Received Packet Size: %d bytes\n", pkthdr.len); 
	printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ? "Ethernet" : "Unknown"); 
	printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ? "IPv4" : "Unknown"); 
	printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST)? "ARP Request" : "ARP Reply");

	/*printf("Hardware type: %04x\n", ntohs(arpheader->htype));
	printf("Protocol type: %04x\n", ntohs(arpheader->ptype));
	printf("Operation: %04x\n", ntohs(arpheader->oper));*/
	printf("hlen: %02x\n", arpheader->hlen);
	printf("plen: %02x\n", arpheader->plen);

	/* If is Ethernet and IPv4, print packet contents */ 
	if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x0800){ 
		printf("Sender MAC: "); 
			
		for(i=0; i<6;i++)
			printf("%02X:", arpheader->sha[i]); 

		printf("\nSender IP: "); 

		for(i=0; i<4;i++)
			printf("%d.", arpheader->spa[i]); 

		printf("\nTarget MAC: "); 

		for(i=0; i<6;i++)
			printf("%02X:", arpheader->tha[i]); 

		printf("\nTarget IP: "); 

		for(i=0; i<4; i++)
			printf("%d.", arpheader->tpa[i]); 

		printf("\n"); 
	} 

}



