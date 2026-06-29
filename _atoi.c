#include <stdio.h>

int my_atoi(char *string){
	int res = 0;
	int i = 0;
	int is_negative = 0;
	if (string[0] == '-'){
		is_negative = 1;
		i = 1;
	}
	for (; string[i] != '\0'; i++){
		if (string[i] < '0' || string[i] > '9'){
			break;
		}
		res = (res * 10) + (string[i] - '0');
	}
	if (is_negative){
		res = -res;
	}
	return res;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage <%s> string\n", argv[0]);
		return -1;
	}

	char *input_str = argv[1];
	int conversion = my_atoi(input_str);
	printf("string version: %s\n", input_str);
	printf("integer version: %d", conversion);
	printf("\n");
	return 0;
}
