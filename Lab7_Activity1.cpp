#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node
{
    char data;
    Node* next;
};

// Linked stack operations
void push(Node*& top, char value) {
    top = new Node{value, top};
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* oldTop = top;
    char value = oldTop->data;
    top = oldTop->next;
    delete oldTop;
    return value;
}

char peek(Node* top) {
    return (top == nullptr) ? '\0' : top->data;
}

bool isEmpty(Node* top) {
    return top == nullptr;
}

// TODO 1: return 2 for * and /; 1 for + and -; 0 otherwise.
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// TODO 2: Convert a valid infix expression to postfix.
// Assume single character operands and operators +,-, *, /.
// Expressions may contain matching parentheses, without spaces.
string infixToPostfix(string infix) {
    Node* top = nullptr;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(static_cast<unsigned char>(ch))) {
            postfix += ch;
        } else if (ch == '(') {
            push(top, ch);
        } else if (ch == ')') {
            while (!isEmpty(top) && peek(top) != '(') {
                postfix += pop(top);
            }
            if (!isEmpty(top) && peek(top) == '(') {
                pop(top);
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!isEmpty(top) && peek(top) != '(' && precedence(peek(top)) >= precedence(ch)) {
                postfix += pop(top);
            }
            push(top, ch);
        }
    }

    while (!isEmpty(top)) {
        postfix += pop(top);
    }

    return postfix;
}

int main() {
    string expression;
    cout << "Enter infix expression: ";
    cin >> expression;
    cout << "Postfix: " << infixToPostfix(expression) << endl;
    return 0;
}
