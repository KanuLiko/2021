#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

/*
*./ledtest /dev/100ask_led0 on
*./ledtest /dev/100ask_led1 off
*/

int main(int argc,char **argv){
	int fd;
	char status;
	
//judge the args
	if(argc !=3){
		printf("Usage:%s <dev> <on|off>\n",argv[0]);
		return -1;
	}
	
//open file
	fd = open(argv[1],O_RDWR);
	if(fd==-1){
		printf("Can not open file %s\n",argv[1]);
		return -1;
		}
	
//write file
	if(strcmp(argv[2],"on")==0){
		status = 1;
		write(fd,&status,1);
		}
		else{
		status = 0;
		write(fd,&status,1);
			}
		
	close(fd);
	return 0;
}
