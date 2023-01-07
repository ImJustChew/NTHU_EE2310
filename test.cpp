#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <cmath>

using namespace std;

typedef double (*FuncPtr)(double);


// Returns the precedence of the given operator
int precedence(string op)
{
    if (op == "^")
        return 3;
    if (op == "*" || op == "/")
        return 2;
    if (op == "+" || op == "-")
        return 1;
    return -1;
}

// Performs the given operation with the given operands
double performOp(double op1, char op, double op2)
{
    if (op == '+')
        return op1 + op2;
    if (op == '-')
        return op1 - op2;
    if (op == '*')
        return op1 * op2;
    if (op == '/')
        return op1 / op2;
    if (op == '^')
        return pow(op1, op2);
}

class Expression
{
private:
    string expr;

public:
    // Constructor
    Expression() {}

    // Input function to read in the expression as a string
    void input()
    {
        cout << "Enter an expression: ";
        getline(cin, expr);

        //regex to detect log_{base}(number), capture base and number
        regex log_regex("log_\\{([0-9]+)\\}\\(([0-9]+)\\)");
        expr = regex_replace(expr, log_regex, "(log($2)/log($1))"); //normalize log, replace with log(number)/log(base)
        cout << expr << endl;
         
    }

    // Evaluate the expression
    void eval()
    {
        stack<double> operands;
        stack<string> operators;

        bool unary = true;
        for (int i = 0; i < expr.size(); i++)
        {
            // If the current character is a digit or a period, parse the number and push it onto the operands stack
            cout << "read: " << expr[i] << endl;
            if (isdigit(expr[i]) || expr[i] == '.')
            {
                char *endptr;
                double num = strtod(&expr[i], &endptr);
                i += endptr - &expr[i] - 1;
                operands.push(num);
                unary = false;
            }
            // If the current character is a unary minus, negate the next number
            else if (expr[i] == '-' && unary)
            {
                i++;
                char *endptr;
                double num = strtod(&expr[i], &endptr);
                i += endptr - &expr[i] - 1;
                operands.push(-num);
                unary = false;
            }
            // If the current character is an operator or function, perform the appropriate operations
            else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^' || isalpha(expr[i]))
            {
                // Parse the function name
                string func;
                while (i < expr.size() && (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^' || isalpha(expr[i])))
                {
                    func += expr[i];
                    i++;
                }
                operators.push(func);
                while (!operators.empty() && precedence(operators.top()) > precedence(func))
                {
                    //print out both stacks
                    cout << "operands: ";
                    stack<double> temp = operands;
                    while (!temp.empty())
                    {
                        cout << temp.top() << " ";
                        temp.pop();
                    }
                    cout << endl;
                    cout << "operators: ";
                    stack<string> temp2 = operators;
                    while (!temp2.empty())
                    {
                        cout << temp2.top() << " ";
                        temp2.pop();
                    }
                    cout << endl;
                    string op = operators.top();
                    operators.pop();
                    double op2 = operands.top();
                    operands.pop();
                    double op1 = operands.top();
                    operands.pop();
                    cout << "normal: " << op1 << " " << op << " " << op2 << endl;
                    cout << "--------------------" << endl;
                    operands.push(performOp(op1, op, op2));
                }
                operators.push(expr[i]);
                unary = true;
            }
            else if (expr[i] == '(')
            {
                operators.push(expr[i]);
                cout << "Pushed ( onto operators stack" << endl;
                unary = true;
            }
            else if (expr[i] == ')')
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    //print out both stacks
                    cout << "operands: ";
                    stack<double> temp = operands;
                    while (!temp.empty())
                    {
                        cout << temp.top() << " ";
                        temp.pop();
                    }
                    cout << endl;
                    cout << "operators: ";
                    stack<char> temp2 = operators;
                    while (!temp2.empty())
                    {
                        cout << temp2.top() << " ";
                        temp2.pop();
                    }
                    cout << endl;
                    char op = operators.top();
                    operators.pop();
                    double op2 = operands.top();
                    operands.pop();
                    double op1 = operands.top();
                    operands.pop();
                    // debug
                    cout << "closing: " << op1 << " " << op << " " << op2 << endl;
                    cout << "--------------------" << endl;
                    operands.push(performOp(op1, op, op2));
                }
                // Pop the '(' from the operators stack
                if (!operators.empty())
                {
                    operators.pop();
                    cout << "Popped ( from operators stack" << endl;
                }
                unary = false;
            }
            else
            {
                unary = false;
            }
        }
        // Perform remaining operations until the operators stack is empty
        while (!operators.empty())
        {
            char op = operators.top();
            operators.pop();
            double op2 = operands.top();
            operands.pop();
            double op1 = operands.top();
            operands.pop();
            // debug
            cout << "final: " <<  op1 << " " << op << " " << op2 << endl;
            operands.push(performOp(op1, op, op2));
        }
        // The final result is the only remaining element on the operands stack
        cout << operands.top() << endl;
    }
};

int main()
{
    Expression exp1;
    exp1.input();
    exp1.eval();
    return 0;
}
