#include <stdio.h>
#include "senser_networkScan.h"

#define BUFFER_SIZE 255

int main(int argc, char *argv[])
{
	network_grub_args n_args;
	pthread_t t_id1;
	int state1 = 0;
	int pipeFd = 0;
	int i;
	int readn;
	char buffer[BUFFER_SIZE] = {0,};
	char *token_order, *token_ip;
	u_char ip[4] = {0,};
	
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

//	while(1) {
//		sleep(60);
//	}

	if( (pipeFd = open(".write_sense", O_RDWR)) < 0) {
		perror("fail to call open()");
		exit(1);
	}

	// pipe 데이터 기다리는 부분
	while(1) {
		if ((readn = read(pipeFd, buffer, BUFFER_SIZE)) < 0) {
			perror("read error");
			exit(1);
		}
		else {
			int flag_order = 0;
			// 데이터 받았으면 buffer에 ip들어감
			buffer[strlen(buffer)-1] = '\0';

			//head 분리
			token_order = strtok(buffer, " ");
			if(strcmp(token_order, "kill") == 0) {
				puts("kill");
				flag_order = 1;

			} else if( strcmp(token_order, "pass") == 0) {
				puts("pass");
				flag_order = 2;
			}

			token_order = strtok(NULL, " ");

			// IP 분리
			token_ip = strtok(token_order, ".");
			ip[0] = atoi(token_ip);
			for (i = 1; i <= 3; i++) {
				token_ip = strtok(NULL, ".");
				ip[i] = atoi(token_ip);
			}
			
			// kill & pass
			if(flag_order == 1) {
				printf("kill ip = %d\n",ip[3]);
				n_args.k_list.target_ip[ip[3]] = 1;
			}else if(flag_order == 2) {
				printf("pass ip = %d\n",ip[3]);
				n_args.k_list.target_ip[ip[3]] = 0;
			}

			


			/*
			// brain으로 데이터 보낼 땐, 이렇게 쓰면 됨
			if ((writen = write(pipeFd, buffer, sizeof(buffer))) < 0) {
			perror("write error");
			exit(1);
			}
			 */
		}
	}



	close(pipeFd);
	return 0;
}
