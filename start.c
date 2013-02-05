#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>


int main(int argc, char* argv[]) {
	char dir[100];
	int pid;
	pid = fork();
	if(pid==0)
		execl("/usr/bin/banner", "banner", "Freezing", (char*)NULL);
	else
		wait(pid);
	pid = fork();
	if(pid==0)
		execl("/usr/bin/banner", "banner", "Cyril", (char*)NULL);
	else
		wait(pid);
	
	printf("Enter the absolute path of the directory that you want to share\n");
	printf("**NOTE: Directory will be created if it doesn't exist**\n");
	scanf("%s", dir);
	pid = fork();
	if(pid==0) {
		struct stat s;
		int test = stat(dir, &s);
		if(S_ISDIR(s.st_mode))
			printf("Directory Name will be shared\n");
		else {
			execl("/bin/mkdir", "mkdir", dir, (char*)NULL);
			printf("Directory created at %s. This directory will be stored\n", dir);
		}
	} else
		wait(pid);

	return 0;
}
