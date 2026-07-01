#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int opt_encrypt(char *input_file){
	FILE *fp_in;
	char *entropy_tap = "/dev/urandom";
	fp_in = fopen(input_file, "rb");
	if (!fp_in){
		fprintf(stderr, "failed to open file\n");
		return -1;
	}
	FILE *pentrophy_tap;
	pentrophy_tap = fopen(entropy_tap, "rb");
	if (!pentrophy_tap){
		fprintf(stderr, "entropy_tap failed to open\n");
		return -1;
	}

	FILE *fp_out;
	FILE *pkey;
	int r = rand() % 10000;
	char cipher_file[256];
	char key_file[256];
	sprintf(cipher_file, "%s_%d.cipher", input_file, r);
	fp_out = fopen(cipher_file, "wb");
	sprintf(key_file, "%s_%d.key", input_file, r); 
	pkey = fopen(key_file, "wb");

	int ch;
	int byte;
	while ((ch = fgetc(fp_in)) != EOF){
		byte = fgetc(pentrophy_tap);
		if (byte == EOF){
			break;
		}
		fwrite(&byte, 1, 1, pkey);
		int cipher_byte = ch ^ byte;
		fwrite(&cipher_byte, 1, 1, fp_out);
	}
	fclose(fp_in);
	fclose(fp_out);
	fclose(pentrophy_tap);
	fclose(pkey);
	return 0;
}

int opt_decrypt(char *encrypted_file, char *key_file){
	return 0;
}

int main(int argc, char *argv[]){
	char *_e = "-e";
	char *_d = "-d";
	char *input = argv[1];
	if (strcmp(input, _e) == 0){
		if (argc != 3){
			fprintf(stderr, "Usage: %s -e filename\n", argv[0]);
			return -1;
		}
		char *input_file = argv[2];
		opt_encrypt(input_file);
	} else if (strcmp(input, _d) == 0){
		if (argc != 4){
			fprintf(stderr, "Usage: %s -d encrypted_filename key_file\n", argv[0]);
			return -1;
		}
		char *encrypted_file = argv[2];
		char *key_file = argv[3];
		opt_decrypt(encrypted_file, key_file);
	} else {
		fprintf(stderr, "Error: Unknown flag '%s'. Use -e or -d.\n", input);
		return -1;
	}
	return 0;
}
