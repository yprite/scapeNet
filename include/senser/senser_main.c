
#include <stdio.h>
#include "senser_networkScan.h"

int main(int argc, char *argv[])
{
	// int i;
	NodeStatus node_status;
	memset(&node_status, 0, sizeof(NodeStatus));
	printf("network Scaning\n");

	networkScan(&node_status);
	return 0;
}