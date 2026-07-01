#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define BUFF_SIZE 4096
int file_encrypter(char *source_file, char *secret_key){
	FILE *fp;
	fp = fopen(source_file, "rb");
	if (!fp){
		fprintf(stderr, "couldnt open file: %s\n", source_file);
		return -1;
	}
	srand(time(NULL));
	int r_int = rand() % 10000;
	char dest_file[256];
	sprintf(dest_file, "%s_%d.dat", source_file, r_int);
	FILE *fp_out = fopen(dest_file, "wb");
	if (!fp_out){
		fprintf(stderr, "fp_out err\n");
		fclose(fp);
		return -1;
	}
	size_t bytes_read;
	char buffer[BUFF_SIZE];
	size_t pass_len = strlen(secret_key);
	if (pass_len == 0){
		fprintf(stderr, "secret_key is empty\n");
		return -1;
	}
	size_t j = 0;
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0){
		size_t i;
		for (i = 0; i < bytes_read; i++){
			buffer[i] = buffer[i] ^ secret_key[j];
			j++;	
			if (j >= pass_len){
				j = 0;
			}
		}
		fwrite(buffer, 1, bytes_read, fp_out);
	}
	fclose(fp);
	fclose(fp_out);
	return 0;
}

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "Usage: %s source_file dest_file secret_key \n", argv[0]);
		return -1;
	}
	char *source_file = argv[1];
	char *secret_key = argv[2];
	int encrtypted = file_encrypter(source_file, secret_key);
	return encrtypted;
}
