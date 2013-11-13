#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int main(int argc, char **argv){

	char *str="!@210.118.34.70&22&u8000&210.118.34.55";
	char *limit_traffic = "8340";
	char *user_traffic;
	char measure[4][100];
	char tempstr[100],dststr[100];	
	int len=0,len_usertr=0,x=0,y=0,z=0;
	char *ptr;
	
	if(str[0]=='!'&&str[1]=='@'){
		strcpy(tempstr, str);
		printf("트래픽 체크 문자열\n");
		len = strlen(tempstr);
		for(x=0; x<len; x++){
			dststr[x]=tempstr[x+2];
		}		
		printf("dststr : %s\n", dststr);
		ptr = strtok(dststr, "&");
		while(ptr != NULL){
			strcpy(	measure[y++],ptr);
			printf("parsing( & ) : %s\n", ptr);
			ptr = strtok(NULL, "&");
		}
		printf("%s\n", measure[0]);	
		printf("%s\n", measure[1]);	
		if(measure[2][0] == 'u'){
			len_usertr=strlen(measure[2])-1;
			user_traffic=(char*)malloc(sizeof(char)*len_usertr);		
			printf("length of measure[1] : %d\n", len_usertr);
			for(x=0; x<len_usertr; x++){
				printf("%d : %c\n", x, measure[2][x+1]);
				user_traffic[x]=measure[2][x+1];		
			
			}
			printf("user_traffic : %s\n", user_traffic);
			z=strcmp(limit_traffic, user_traffic); 
			// z>0, limit_traffic
			// z=0, same
			// z<0, user_traffic
			printf("value : %d\n", z);
			
		}
		printf("\n%s\n", measure[2]);	
		printf("%s\n", measure[3]);	

		
	}
//	else if(str[0] == '!' && str[1] == 


	return 0;
}
