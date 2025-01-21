#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> 

#define MAX_STACK_SIZE 100
#define MAX_EXP_SIZE 100


float calc_stack[MAX_STACK_SIZE];
int top_index = -1;

// Function to check if the stack is empty
int stack_is_empty(void) {
    return (top_index < 0);
}

// Function to check if the stack is full
int stack_is_full(void) {
    return (top_index >= MAX_STACK_SIZE - 1);
}

// Function to push a number into the stack
void stack_push(float value) {
    if (!stack_is_full()) {
        top_index++;
        calc_stack[top_index] = value;
    } else {
        printf("Stack overflow!\n");
    }
}

// Function to pop a number from the stack
float stack_pop(void) {
    if (!stack_is_empty()) {
        float popped_value = calc_stack[top_index];
        top_index--;
        return popped_value;
    } else {
        printf("Error: Stack underflow!\n");
        return 0;
    }
}

// Basic arithmetic functions
float add(float num1, float num2) { return num1 + num2; }
float subtract(float num1, float num2) { return num1 - num2; }
float multiply(float num1, float num2) { return num1 * num2; }
float divide(float num1, float num2) {
    if (num2 != 0) return num1 / num2;
    printf("Division by zero!\n");
    return 0;
}

// New mathematical functions
float sine(float x) { 
    return sinf(x); 
}

float cosine(float x) 
{
    return cosf(x); 
}

float tangent(float x) 
{ 
    return tanf(x); 
}

float natural_log(float x) {
    if (x > 0) return logf(x);
    printf("Logarithm of non-positive value!\n");
    return 0;
}

float base10_log(float x) {
    if (x > 0) return log10f(x);
    printf("Logarithm of non-positive value!\n");
    return 0;
}

float exponential(float x) 
{ 
    return expf(x); 
}

float power(float base, float exp) 
{ 
    return powf(base, exp); 
}


// Main function to process the RPN expression
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    // Process each argument as part of the RPN expression
    for (int i = 1; i < argc; i++) {
        char *current_arg = argv[i];

        if (isdigit(current_arg[0]) || 
            (current_arg[0] == '-' && isdigit(current_arg[1]))) {
            // If the argument is a number, push it onto the stack
            float number = atof(current_arg);
            stack_push(number);
        } else if (strcmp(current_arg, "+") == 0) {
            stack_push(add(stack_pop(), stack_pop()));
        } else if (strcmp(current_arg, "-") == 0) {
            float op2 = stack_pop();
            float op1 = stack_pop();
            stack_push(subtract(op1, op2));
        } else if (strcmp(current_arg, "*") == 0) {
            stack_push(multiply(stack_pop(), stack_pop()));
        } else if (strcmp(current_arg, "/") == 0) {
            float op2 = stack_pop();
            float op1 = stack_pop();
            stack_push(divide(op1, op2));
        } else if (strcmp(current_arg, "sin") == 0) {
            stack_push(sine(stack_pop()));
        } else if (strcmp(current_arg, "cos") == 0) {
            stack_push(cosine(stack_pop()));
        } else if (strcmp(current_arg, "tan") == 0) {
            stack_push(tangent(stack_pop()));
        } else if (strcmp(current_arg, "log") == 0) {
            stack_push(natural_log(stack_pop()));
        } else if (strcmp(current_arg, "log10") == 0) {
            stack_push(base10_log(stack_pop()));
        } else if (strcmp(current_arg, "exp") == 0) {
            stack_push(exponential(stack_pop()));
        } else if (strcmp(current_arg, "^") == 0) {
            float exp = stack_pop();
            float base = stack_pop();
            stack_push(power(base, exp));
        } else {
            printf("Unknown operator: %s\n", current_arg);
        }
    }

    // The final result 
    if (!stack_is_empty()) {
        printf("Result: %.2f\n", stack_pop());
    } else {
        printf("No result found.\n");
    }

    return 0;
}
