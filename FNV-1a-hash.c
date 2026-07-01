#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

void lower_str(char *string){
	int i;
	for (i = 0; i < strlen(string); i++){
		string[i] = tolower((unsigned char)string[i]);
	}
}

unsigned long hash(char *password){
	unsigned long offset_basis = 2166136261;
	unsigned long fnv_prime = 16777619;
	lower_str(password);
	int ch;
	for (ch = 0; password[ch] != '\0'; ch++){
		char c = password[ch];
		offset_basis = offset_basis ^ c;
		offset_basis = offset_basis * fnv_prime;
	}
	return offset_basis;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s password\n", argv[0]);
		return -1;
	}
	char *password = argv[1];
	if (!password) {
		fprintf(stderr, "Password err: %s\n", password);
		return -1;
	}
	uint32_t hashed;
	hashed = hash(password);
	printf("Password hashed using FNV-1a algorithm: %08x\n", hashed);
	return 0;

}
