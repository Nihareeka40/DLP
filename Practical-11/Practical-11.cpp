#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempVarCount = 1;

string getTempVar() {
    return "t" + to_string(tempVarCount++);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void generateQuadruple(char op, string val1, string val2) {
    string temp = getTempVar();
    quadruples.push_back({string(1, op), val1, val2, temp});
}

void processStacks(stack<char> &ops, stack<string> &vals) {
    char op = ops.top(); ops.pop();
    string val2 = vals.top(); vals.pop();
    string val1 = vals.top(); vals.pop();
    generateQuadruple(op, val1, val2);
    vals.push(quadruples.back().result);
}

void parseExpression(string expr) {
    stack<char> ops;
    stack<string> vals;
    stringstream ss(expr);
    char token;
    
    while (ss >> token) {
        if (isdigit(token)) {
            ss.putback(token);
            int num;
            ss >> num;
            vals.push(to_string(num));
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                processStacks(ops, vals);
            }
            ops.pop(); // Remove '('
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                processStacks(ops, vals);
            }
            ops.push(token);
        }
    }
    
    while (!ops.empty()) {
        processStacks(ops, vals);
    }
}

void printQuadruples() {
    cout << "Operator    Operand 1    Operand 2    Result" << endl;
    for (const auto &q : quadruples) {
        cout << q.op << "           " << q.arg1 << "          " << q.arg2 << "          " << q.result << endl;
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);
    parseExpression(expression);
    printQuadruples();
    return 0;
}
