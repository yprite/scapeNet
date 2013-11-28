#include <linux/ip.h>             
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/netdevice.h>      
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_arp.h>
#include <linux/skbuff.h>         
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/string.h>
#include <linux/ipv6.h> 
#include <linux/inet.h>
#include <linux/delay.h>
#include <linux/if_arp.h>

#define ARP_REQUEST	1
#define ARP_REPLY	2

#define SIZE 50

MODULE_LICENSE("GPL");

typedef struct arphdr_t {
	__be16      ar_hrd;     /* format of hardware address   */
	__be16      ar_pro;     /* format of protocol address   */
	unsigned char   ar_hln;     /* length of hardware address   */
	unsigned char   ar_pln;     /* length of protocol address   */
	__be16      ar_op;      /* arp opcode (command)     */

	unsigned char       ar_sha[6];   /* sender hardware address  */
	unsigned char       ar_sip[4];      /* sender ip address        */
	unsigned char       ar_tha[6];   /* target hardware address  */
	unsigned char       ar_tip[4];      /* target ip address        */
}arphdr_t;


unsigned int main_hook(unsigned int hooknum,  
						struct sk_buff *skb,
						const struct net_device *in,
						const struct net_device *out,
						int (*okfn)(struct sk_buff*)
						);

static struct nf_hook_ops netfilter_ops[] = {
	{
		.hook           = main_hook,
		.pf             = NFPROTO_ARP,
		.hooknum        = NF_ARP_IN,
	},
	{
		.hook           = main_hook,
		.pf				= PF_INET,
		.hooknum		= NF_INET_PRE_ROUTING,
	},
};

int set_kfifo1(char *msg);
int set_kfifo(char *msg);
void send_myfifo(char *filename, char *msg);
static struct nf_hook_ops netfilter_ops_out; /* NF_IP_POST_ROUTING */

struct sk_buff *sock_buff;
struct ethhdr *eth_header;
struct arphdr_t *arp_header;
struct iphdr *ip_header;
struct tcphdr *tcp_header;
//int dadd,sadd,bit1,bit2,bit3,bit4;
struct net_device * dev;

void print_traffic(void) {
	char buf[SIZE];
	int i = 0;
	unsigned int *temp_ip;
	unsigned char temp_protocol;
    int sip[4] = {0,};
    int tip[4] = {0,};

	temp_ip = &(ip_header->saddr);
    for(i=0; i<4; i++) {
		sip[i] = *( ((unsigned char*)temp_ip) + i);
    }

	temp_ip = &(ip_header->daddr);
    for(i=0; i<4; i++) {
		tip[i] = *( ((unsigned char*)temp_ip) + i);
    }

	temp_protocol = ip_header->protocol;
	//printk("protocol = %02x\n",temp_protocol);

	//printk("test_HW %d\n",ntohs(tcp_header->window));
	//printk("Sourcee Port %d\n", ntohs(tcp_header->source) );
	//printk("Dest Port %d\n\n", ntohs(tcp_header->dest) );

	if(sip[3] == 1 || tip[3] == 1)
		return ;

	if(sip[0] == 210 && sip[1] == 118 && sip[2] == 34){
		sprintf(buf,"D@%d.%d.%d.%dL%dLu%dL%d.%d.%d.%d", 
		sip[0], sip[1], sip[2], sip[3], 
		ntohs(tcp_header->dest), ntohs(ip_header->tot_len), tip[0], tip[1], tip[2], tip[3]);
	} else {
		sprintf(buf,"D@%d.%d.%d.%dL%dLd%dL%d.%d.%d.%d", 
		tip[0], tip[1], tip[2], tip[3], 
		ntohs(tcp_header->source), ntohs(ip_header->tot_len), sip[0], sip[1], sip[2], sip[3]);
	}
	set_kfifo(buf);
	//send_myfifo("../bin/read_sense", buf);
}

void print_arp(void)
{
	int i = 0;
	char buf[SIZE];


	if(ntohs(arp_header->ar_op) == ARP_REQUEST)
		return ;

	if(ntohs(arp_header->ar_hrd) == 1 && ntohs(arp_header->ar_pro) == 0x0800) {
		if(arp_header->ar_sip[3] == 1)
			return ;

		printk("Receiver IP : ");
		for(i=0; i<4; i++)
			printk("%d.", arp_header->ar_sip[i]);
		printk("\n");

		sprintf(buf, "D~%d.%d.%d.%d\n", 
		arp_header->ar_sip[0],arp_header->ar_sip[1],arp_header->ar_sip[2],arp_header->ar_sip[3]);

		set_kfifo1(buf);
		//send_myfifo("../bin/read_sense", buf);
	}

	return ;
}

/* Function prototype in <linux/netfilter> */
unsigned int main_hook(unsigned int hooknum,  
						struct sk_buff *skb,
						const struct net_device *in,
						const struct net_device *out,
						int (*okfn)(struct sk_buff*)
						)
{
	unsigned int *temp_ip;
	unsigned char temp_protocol;
	sock_buff=skb_copy(skb,GFP_ATOMIC);

	eth_header = eth_hdr(skb);

	//printk("ether pro =  %d\n", eth_header->h_proto);

	if(ntohs(eth_header->h_proto) == 0x0806) {
		//arp_header = (struct arphdr_t*)( (char *)eth_header + sizeof(arphdr_t));
		arp_header = arp_hdr(skb);

		print_arp();

		return NF_ACCEPT;
	} else if(ntohs(eth_header->h_proto) == 0x0800) {
		//ip_header=(struct iphdr*)(sock_buff->network_header);
		ip_header = ip_hdr(skb);

		if(ip_header->protocol != 0x6) {	//nat tcp
			return NF_ACCEPT;
		}
		tcp_header = (struct tcphdr*)( (char *)ip_header + sizeof(struct iphdr) );
		//tcp_header = tcp_hdr(skb);

		print_traffic();
	}
	
	return NF_ACCEPT;
}

int init_module(void)
{
	nf_register_hooks(netfilter_ops, ARRAY_SIZE(netfilter_ops));
	
	return 0;
}

void cleanup_module(void)
{
	printk("test_cleanup_1\n");

	nf_unregister_hooks(netfilter_ops, ARRAY_SIZE(netfilter_ops));
}
