#include<stdio.h>

int main(int argc, char* argv[]) {
	if(argc!=3)
		printf("Usage: ./copy <src file> <dst file>\n");
	FILE *src=NULL, *dst=NULL;
	src = fopen(argv[1], "r");
	dst = fopen(argv[2], "w");
	char line[80];
	while(fgets(line, 80, src))
		fprintf(dst, "%s", line);
	fclose(src);
	fclose(dst);
	return 0;
}
