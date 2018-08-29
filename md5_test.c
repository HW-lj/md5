#include <stdio.h>
#include <string.h>
#include "md5.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	//printf("%s\n", md5_encrypt(argv[1], strlen(argv[1])));

	if(2 != argc)
	{
		fprintf(stderr, "Usage error!\n"); //标准错误输出
		return 1;
	}

	FILE* fp = NULL;
	int file_size = 0;
	
	unsigned char *buff = NULL;

	fp = fopen(argv[1], "rb");
	
	if(NULL == fp)
	{
		perror("fopen");
		return 1;
	}

	fseek(fp, 0, 2);
	file_size = ftell(fp); 
	rewind(fp);

	buff = malloc(file_size);
	if(NULL == buff)
	{
		perror("allocate memory fail");
		fclose(fp);
		return 1;
	}

	if(fread(buff, 1, file_size, fp) != file_size)
	{
		fprintf(stderr, "read %s fail!\n", argv[1]);
		fclose(fp);
		return 1;
	}

	fclose(fp);

	printf("%s\n", md5_encrypt(buff, file_size));

	free(buff);
		
	return 0;
}
