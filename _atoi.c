#include <stdio.h>

int my_atoi(char *string){
	int res = 0;
	int i;
	for (i = 0; string[i] != '\0'; i++){
		res = (res * 10) + (string[i] - '0');
	}
	return 0;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage <%s> string\n", argv[0]);
		return -1;
	}

	char *input_str = argv[1];
	int conversion = my_atoi(input_str);
	printf("string version: %s", input_str);
	printf("integer version: %d", conversion);
	return 0;
}
