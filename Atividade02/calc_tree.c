#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
  char character;
  int value;
  struct Node * next;
  struct Node * left_child;
  struct Node * right_child;

}
Node;

int isEmpty(Node * stack) {
  return stack == NULL;
}

void ipush(Node ** top, int item) {
  Node * temp = (Node * ) malloc(sizeof(Node));
  temp -> value = item;
  if (isEmpty( * top)) {
    temp -> next = NULL;
  } else {
    temp -> next = * top;
  }

  * top = temp;
}

//
void push(Node ** top, char item) {
  Node * temp = (Node * ) malloc(sizeof(Node));

  temp -> character = item;
  if (isEmpty( * top)) {
    temp -> next = NULL;
  } else {
    temp -> next = * top;
  }

  * top = temp;
}

void pushNode(Node ** top, Node * x) {
  if ( * top == NULL) {
    * top = x;
  } else {
    x -> next = * top;
    * top = x;
  }
}

Node * pop(Node ** top) {
  Node * temp = (Node * ) malloc(sizeof(Node));

  if (isEmpty( * top)) {
    exit(1);
  } else {
    temp = * top;
    * top = ( * top) -> next;

    return temp;
  }
}

Node * top(Node * top) {
  if (!isEmpty(top))
    return top;
  else
    exit(1);
}

int opPrecedence(char ch) {
  if (ch == '+' || ch == '-') {
    return 1;
  } else if (ch == '*' || ch == '/') {
    return 1;
  } else {
    return -1;
  }
}

int isOperator(char c) {
  return (c == '/' || c == '*' || c == '+' || c == '-' || c == '(' || c == ')');
}

int convertInfixToPostfix(char * expression) {

  Node * postfixStack = NULL;

  int i, j;

  for (i = 0, j = -1; expression[i]; ++i) {
    if (!isOperator(expression[i])) {
      expression[++j] = expression[i];
    } else if (expression[i] == '(') {
      push( & postfixStack, expression[i]);
    } else if (expression[i] == ')') {
      while (!isEmpty(postfixStack) && top(postfixStack) -> character != '(') {
        expression[++j] = pop( & postfixStack) -> character;
      }
      pop( & postfixStack);
    } else {
      while (!isEmpty(postfixStack) && opPrecedence(expression[i]) <= opPrecedence(top(postfixStack) -> character)) {
        expression[++j] = pop( & postfixStack) -> character;
      }
      push( & postfixStack, expression[i]);
    }

  }

  while (!isEmpty(postfixStack)) {
    expression[++j] = pop( & postfixStack) -> character;
  }

  expression[++j] = '\0';
  printf("Postfix expression: %s", expression);
}

Node * createNode(char item) {
  Node * node = (Node * ) malloc(sizeof(Node));

  node -> character = item;
  node -> value = INT_MIN;
  node -> left_child = NULL;
  node -> right_child = NULL;

  return node;
}

Node * insert(Node ** root, char data) {

  if ( * root == NULL) {
    * root = createNode(data);
  } else {
    if (data < (( * root) -> character)) {
      Node * lChild = insert( & (( * root) -> left_child), data);
      ( * root) -> left_child = lChild;
    } else {
      Node * rChild = insert( & (( * root) -> right_child), data);
      ( * root) -> right_child = rChild;
    }
  }

  return *root;
}

void displayPreOrder(Node * root) {
  if (root != NULL) {
    printf("%c ", root -> character);
    displayPreOrder(root -> left_child);
    displayPreOrder(root -> right_child);
  }
}

void displayInOrder(Node * root) {
  if (root != NULL) {
    displayInOrder(root -> left_child);
    printf("%c ", root -> character);
    displayInOrder(root -> right_child);
  }
}

void displayPostOrder(Node * root) {
  if (root != NULL) {
    displayPostOrder(root -> left_child);
    displayPostOrder(root -> right_child);
    printf("%c ", root -> character);
  }
}

int countNodes(Node * root) {
  if (root == NULL)
    return 0;
  else
    return 1 + countNodes(root -> left_child) + countNodes(root -> right_child);
}

void constructExpressionTree(Node ** tree, char * s) {
  struct Node * x, * y, * z;
  for (int i = 0; i < s[i]; i++) {
    if (isOperator(s[i])) {
      printf("Inserting operator: %c\n", s[i]);
      z = createNode(s[i]);
      x = pop(tree);
      y = pop(tree);
      z -> left_child = y;
      z -> right_child = x;
      pushNode(tree, z);
    } else {
      printf("Inserting value: %c\n", s[i]);
      z = createNode(s[i]);
      z -> value = s[i] - '0';
      pushNode(tree, z);
    }
  }
}

int evaluateExpressionTree(Node ** tree) {
  if (isEmpty( * tree))
    return 0;

  if (isEmpty(( * tree) -> left_child) && isEmpty(( * tree) -> right_child)) {
    return ( * tree) -> value;
  }

  int l_val = evaluateExpressionTree( & (( * tree) -> left_child));

  int r_val = evaluateExpressionTree( & (( * tree) -> right_child));

  if (( * tree) -> character == '+') {
    return l_val + r_val;
  } else if (( * tree) -> character == '-') {
    return l_val - r_val;
  } else if (( * tree) -> character == '*') {
    return l_val * r_val;
  } else {
    return l_val / r_val;
  }

}

int main() {
  Node * tree = NULL;
  char expression[] = "(2+(1*3))-3";

  convertInfixToPostfix(expression);
  constructExpressionTree( & tree, expression);

  printf("\n");
  displayPreOrder(tree);
  printf("\n");
  displayInOrder(tree);
  printf("\n");
  displayPostOrder(tree);
  printf("\n");

  int result = evaluateExpressionTree( & tree);
  printf("Result: %d\n", result);

  return 0;
}
