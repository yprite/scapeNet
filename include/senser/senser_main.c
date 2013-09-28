
#include <stdio.h>
#include "senser_networkScan.h"

int main(int argc, char *argv[])
{
	int i;
	NodeStatus node_status;
	memset(&node_status, 0, sizeof(NodeStatus));
	printf("network Scaning\n");

	networkScan(&node_status);

	printf("network node status!!!!\n");
	for(i=1; i<255; i++) {
		if(node_status.node[i].status == 1) {
			printf("%6d", i);
		} else {
			printf("%6d", 0);
		}

		if(i%15 == 0)
			puts("");
	}
	puts("");
	return 0;
}