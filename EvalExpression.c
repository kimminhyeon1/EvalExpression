#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType* sptr) {
	sptr->top = -1;
}
int is_empty(StackType* sptr) {
	return (sptr->top == -1);
}
int is_full(StackType* sptr) {
	return(sptr->top == (MAX_STACK_SIZE-1));
}
void push(StackType* sptr, element item) {
	if (is_full(sptr)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else sptr->data[++(sptr->top)] = item;
}
element pop(StackType* sptr) {
	if (is_empty(sptr)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return sptr->data[(sptr->top)--];
}
int eval(char *exp) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init(&s);
	for (i = 0; i < len; i++) {
		printf("expression: %c\n", exp[i]);
		ch = exp[i];
		if ((ch == '+') || (ch == '-')
			|| (ch == '*') || (ch == '/')) {
			op1 = pop(&s);
			op2 = pop(&s);
			switch (ch) {
			case '+': push(&s, op2 + op1); break;
			case '-':push(&s, op2 - op1); break;
			case '*':push(&s, op2 * op1); break;
			case '/':push(&s, op2 / op1); break;
			default:;
			}
		}
		else if ((ch >= '0') && (ch <= '9')) {
			value = ch - '0';
			push(&s, value);
		}
	}
	return pop(&s);
}
int main() {
	char expression[MAX_STACK_SIZE];
	int result;

	printf("postfix Expression: ");
	fgets(expression, sizeof(expression), stdin);

	result = eval(expression);
	printf("Result: %d\n", result);

	return 0;
}