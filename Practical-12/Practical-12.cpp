#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <cctype>
using namespace std;

// Function to check if a string is a number
bool isNumber(const string &s) {
    return !s.empty() && (isdigit(s[0]) || (s[0] == '.' && s.size() > 1));
}

// Function to perform arithmetic operations
double evaluate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;
        default: return 0;
    }
}

// Function to perform constant folding
string optimizeExpression(const string &expr) {
    stringstream ss(expr);
    vector<string> tokens;
    string token;

    // Tokenizing the input
    while (ss >> token) {
        tokens.push_back(token);
    }

    vector<string> optimized;
    stack<double> values;
    stack<char> operators;

    // Process the tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        if (isNumber(tokens[i])) {
            values.push(stod(tokens[i]));
        } else if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
            operators.push(tokens[i][0]);
        } else {
            // If a variable is encountered, flush the stack and preserve the expression
            while (!operators.empty() && values.size() >= 2) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(evaluate(a, b, op));
            }
            // Move computed constant to output
            if (!values.empty()) {
                optimized.push_back(to_string((int)values.top()));
                values.pop();
            }
            optimized.push_back(tokens[i]);
        }
    }

    // Evaluate remaining expressions
    while (!operators.empty() && values.size() >= 2) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(evaluate(a, b, op));
    }

    // Move final computed value to output
    if (!values.empty()) {
        optimized.push_back(to_string((int)values.top()));
    }

    // Construct optimized expression
    string optimizedExpr;
    for (const string &t : optimized) {
        optimizedExpr += t + " ";
    }

    return optimizedExpr;
}

int main() {
    string expression;
    cout << "Enter arithmetic expression: ";
    getline(cin, expression);

    string optimized = optimizeExpression(expression);
    cout << "Optimized Expression: " << optimized << endl;
    return 0;
}
