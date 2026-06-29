#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int my_grep(char *target, char *file){
	FILE *fp = fopen(file, "r");
	if (!fp){
		fprintf(stderr, "file could not be opened");
		return -1;
	}
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1){
		char *pstart = strstr(line, target);
		if (pstart != NULL){
			size_t target_size = pstart - line;
			fwrite(line, sizeof(char), target_size, stdout);
			int ch;
			for (ch = 0; target[ch] != '\0'; ch++){
				printf("\033[1;31m");
				putchar(target[ch]);
			}
			printf("\033[0m");
			printf("%s", pstart + strlen(target));
		}
	}
	fclose(fp);
	free(line);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc != 3){
		fprintf(stderr, "Usage <%s> word filename\n", argv[0]);
		return -1;
	}

	char *target = argv[1];
	char *filename = argv[2];
	int grepped = my_grep(target, filename);
	return grepped;
	
}
