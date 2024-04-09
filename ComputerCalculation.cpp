#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class MyStack {
private:
    static const int MAX_SIZE = 1000;
    int arr[MAX_SIZE];
    int topIndex;

public:
    MyStack() : topIndex(-1) {}

    void push(int value) {
        if (topIndex >= MAX_SIZE - 1) {
            return;
        }
        arr[++topIndex] = value;
    }

    void pop() {
        if (topIndex >= 0) {
            topIndex--;
        }
    }

    int top() {
        if (topIndex < 0) {
            return -1;
        }
        return arr[topIndex];
    }

    bool empty() {
        return topIndex == -1;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluateExpression(const string& expression) {
    MyStack values;
    MyStack ops;
    size_t i = 0;
    while (i < expression.length()) {
        if (expression[i] == ' ') {
            i++;
            continue;
        } else if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                i++;
            }
            values.push(val);
        } else if (expression[i] == '(') {
            int count = 1;
            string subExpression;
            i++;
            while (i < expression.length() && count!= 0) {
                if (expression[i] == '(') {
                    count++;
                } else if (expression[i] == ')') {
                    count--;
                }
                subExpression += expression[i];
                i++;
            }
            if (subExpression.length() == 0) {
                i++; // Skip the ')' character
            } else {
                int subResult = evaluateExpression(subExpression);
                values.push(subResult);
            }
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            

            if(expression[i] == '-' && isdigit(expression[i + 1])){

                i++;
                int val = 0;

                while (i < expression.length() && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                i++;
                }
            
                val = -val;
            
            values.push(val);
            continue;
            
            }
            
            
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
            i++;
        } else {
            // Handle invalid characters if needed
            i++;
        }
    }
    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    return values.top();
}

int main() {
    std::string inputLine;
    getline(std::cin, inputLine);

    std::stringstream ss(inputLine);
    int n, m;
    ss >> n >> m;

    std::string expression;
    getline(std::cin, expression);

    int result = evaluateExpression(expression);
    std::cout << result << std::endl;

    return 0;
} 