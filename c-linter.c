#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
	int arr[MAX_SIZE];
	int top;
} Stack;

void initialise(Stack *stack){
	stack->top = -1;
}

bool isEmpty(Stack *stack){
	return stack->top == -1;
}
bool isFull(Stack *stack){
	return stack->top >= MAX_SIZE -1;
}

void push(Stack *stack, char value){
	if (isFull(stack)){
		printf("stack overflow err");
		return;
	}
	stack->arr[++stack->top] = value;
}

int pop(Stack *stack){
	if(isEmpty(stack)){
		printf("stack underflow err");
		return -1;
	}

	int popped = stack->arr[stack->top];
	stack->top--;
	return popped;
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}

int linter(char *file){
	Stack stack;
	initialise(&stack);
	char line[100];
	FILE *fp;
	fp = fopen(file, "r");
	if (!fp){
		printf("fp err");
		return -1;
	}
	char open_p = '(';
	char close_p = ')';
	char quotes = '"';

	int line_counter = 1;
	bool inside_string = false;
	while(fgets(line, sizeof(line), fp)){
		for (int i = 0; line[i] != '\0'; i++){
			if (line[i] == quotes){
				inside_string = !inside_string;
				continue;
			}
			if (inside_string){
				continue;
			}
			if (line[i] == open_p){
				push(&stack, line[i]);
			} else if (line[i] == close_p){
				if (stack.top >= 0 && stack.arr[stack.top] == open_p){
					pop(&stack);
				} else {
					printf("ERROR -> mismatched or extra %c\n", close_p);
					printf("LINE -> %d\n", line_counter);
					fclose(fp);
					return -1;
				}
			}  
		}
		line_counter++;
	}
	fclose(fp);
	if (!isEmpty(&stack)){
		printf("ERROR -> missing %c at EOF\n", close_p);
		return -1;
	}
	printf("%s has correct code syntax\n", file);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage <%s> filename", argv[0]);
		return -1;
	}
	char *my_file = argv[1];
	int linted = linter(my_file);
	return linted;
}
