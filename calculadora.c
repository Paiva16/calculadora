  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>
  #include <ctype.h>

  #define MAX_STACK_SIZE 100

  typedef struct {
      double items[MAX_STACK_SIZE];
      int top;
  } Stack;
  //definir overflow
  void push(Stack *s, double value) {
      if (s->top == MAX_STACK_SIZE - 1) {
          printf("Erro: Stack overflow\n");
          exit(EXIT_FAILURE);
      }
      s->items[++(s->top)] = value;
  }
  //definir underflow
  double pop(Stack *s) {
      if (s->top == -1) {
          printf("Erro: Stack underflow\n");
          exit(EXIT_FAILURE);
      }
      return s->items[(s->top)--];
  }

  double evaluatePostfix(char *expression) {
      Stack s;
      s.top = -1;

      char *token = strtok(expression, " ");
      while (token != NULL) {
          if (isdigit(token) || (*token == '-' && isdigit((token + 1)))) {
              push(&s, atof(token));
          } else {
              double op2 = pop(&s);
              double op1 = 0.0;
              double result = 0.0;

              if (strcmp(token, "+") == 0) {
                  op1 = pop(&s);
                  result = op1 + op2;
              } else if (strcmp(token, "-") == 0) {
                  op1 = pop(&s);
                  result = op1 - op2;
              } else if (strcmp(token, "*") == 0) {
                  op1 = pop(&s);
                  result = op1 * op2;
              } else if (strcmp(token, "/") == 0) {
                  op1 = pop(&s);
                  result = op1 / op2;
              } else if (strcmp(token, "^") == 0) {
                  op1 = pop(&s);
                  result = pow(op1, op2);
              } else if (strcmp(token, "raiz") == 0) {
                  result = sqrt(op2);
              } else if (strcmp(token, "sen") == 0) {
                  result = sin(op2);
              } else if (strcmp(token, "cos") == 0) {
                  result = cos(op2);
              } else if (strcmp(token, "tg") == 0) {
                  result = tan(op2);
              } else if (strcmp(token, "log") == 0) {
                  result = log10(op2);
              } else {
                  printf("Operador ou função especial inválida: %s\n", token);
                  exit(EXIT_FAILURE);
              }

              push(&s, result);
          }
          token = strtok(NULL, " ");
      }
      return pop(&s);
  }

  int main() {
      // Teste das expressões previamente definidas
      char expressions[][100] = {
          "3 4 + 5 *",            // 35
          "7 2 * 4 +",            // 18
          "8 5 2 4 + * +",        // 38
          "6 2 / 3 + 4 *",        // 24
          "9 5 2 8 * 4 + * +",    // 109
          "2 3 + log 5 /",        // Aprox. 0.14
          "10 log 3 ^ 2 +",       // 3
          "45 60 + 30 cos *",     // Aprox. 90.93
          "0.5 45 sin 2 ^ +"      // 1
      };

      int num_expressions = sizeof(expressions) / sizeof(expressions[0]);
      //exibir resultados
      for (int i = 0; i < num_expressions; ++i) {
          printf("Expressão: %s\n", expressions[i]);
          double resultado = evaluatePostfix(expressions[i]);
          printf("Resultado: %.2f\n", resultado);
          printf("\n");
      }

      return 0;
  }