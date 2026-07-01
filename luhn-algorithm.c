#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int luhn_check(char *numbers){
	if (numbers == NULL){
		fprintf(stderr, "Invalid number: %d \n", *numbers);
		return -1;
	}
	int length = strlen(numbers);
	int r;
	int move = 0;
	int sum = 0;
	for (r = length - 1; r >= 0; r--){
		if (numbers[r] == ' ' || numbers[r] == '-'){
			continue;
		}
		if (numbers[r] < '0' || numbers[r] > '9'){
			fprintf(stderr, "invalid number: %s", numbers);
			return -1;
		}
		int digit = numbers[r] - '0';
		if (move){
			digit *= 2;
			if (digit > 9){
				digit -= 9;
			}
		}
		sum += digit;
		move = !move;
	}
	
	if (sum % 10 == 0){
		printf("Valid credit card: %s\n", numbers);
	} else {
		printf("Invalid credit card!\n");
	}
	return 0;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s credit-card-number\n", argv[0]);
		return -1;
	}
	char *credit_card_num = argv[1];
	int result = luhn_check(credit_card_num);
	return result;
}
