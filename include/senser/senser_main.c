#include <stdio.h>
#include "senser_networkScan.h"

int main(int argc, char *argv[])
{
	network_grub_args n_args;
	pthread_t t_id1;
	int state1 = 0;
	int i;
	
	printf("network Scaning\n");
	memset(&n_args, 0, sizeof(network_grub_args));
	n_args.g_ip = 1;
	
	state1 = pthread_create(&t_id1, NULL, networkScan, &n_args);
	if(state1 != 0) {
		fprintf(stderr, "pthread_create() error\n");
		return 0;
	}

	printf("count = %d\n", argc);

	if(argc > 1) {
		for(i=1; i<argc; i++) {
			int t_ip = atoi(argv[i]);
			printf("%d\n",t_ip);
			n_args.k_list.target_ip[t_ip] = 1;
		}
	}

	while(1) {
		sleep(60);
	}



	return 0;
}
