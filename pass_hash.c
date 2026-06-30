#include <stdio.h>
// hashing algorithm using DJB2 algorithm
unsigned long hash(char *string){
	unsigned long base_hash_state = 5381;
	int ch;
	for (ch = 0; string[ch] != '\0'; ch++){
		char curr_ch = string[ch];
		base_hash_state = ((base_hash_state << 5) + base_hash_state) ^ curr_ch;
	}
	return base_hash_state;
}
int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s password_to_hash\n", argv[0]);
		return -1;
	}

	char *input_str = argv[1];
	if (!input_str){
		fprintf(stderr, "input_str err\n");
		return -1;
	}
	unsigned long hashed = hash(input_str);
	printf("Password hash: %lx\n", hashed);
	return 0;
}
