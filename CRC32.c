#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

bool is_file(char *input){
	struct stat path;
	if (stat(input, &path) != 0){
		return false;
	}
	return S_ISREG(path.st_mode);
}

int _CRC32(char *input){
	unsigned int crc = 0xFFFFFFFF;
	if (is_file(input)){
		FILE *fp;
		fp = fopen(input, "rb");
		if (!fp){
			fprintf(stderr, "file err");
			return -1;
		}
		char buffer[4096];
		size_t bytes_read;
		size_t i = 0;
		while((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0 ){
			for (i = 0; i < bytes_read; i++){
				crc ^= (unsigned char)buffer[i];
				for (int bit = 0; bit < 8; bit++){
					if (crc & 1){
						crc = (crc >> 1) ^ 0xEDB88320;
					} else {
						crc = crc >> 1;
					}
				}
			}
		}
		fclose(fp);
	}
	return ~crc;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s input", argv[0]);
		return -1;
	}
	char *input = argv[1];
	unsigned int res = _CRC32(input);
	printf("%08x  %s\n", res, input);
	if (res == 0xCBF43926){
		printf("PASSED TEST...: %08x\n", res);
	} else {
		printf("FAILED TEST...: %08x\n", res);
	}
	return 0;
}
