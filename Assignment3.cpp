#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

enum Type
{
    NUM,
    OP,
};

enum assoc
{
    LTR,
    RTL,
    NONE // for unary operators
};

class Operator
{
private:
    string op;
    int precedence;
    assoc associativity;
    double (*func)(double x, double y);

public:
    Operator();
    Operator(string _op, int _precedence, assoc _associativity, double (*func)(double, double));
    friend bool isOp(string s, int i, Operator &op);
    friend class Expression;
};

Operator::Operator()
{
    op = "";
    precedence = 0;
    associativity = LTR;
}

Operator::Operator(string _op, int _precedence, assoc _associativity, double (*_func)(double, double))
{
    op = _op;
    precedence = _precedence;
    associativity = _associativity;
    func = _func;
}

Operator opdef[] = {
    Operator("+", 1, LTR, [](double a, double b)
             { return a + b; }),
    Operator("-", 1, LTR, [](double a, double b)
             { return a - b; }),
    Operator("-", 2, NONE, [](double a, double b)
             { return -a; }),
    Operator("*", 3, LTR, [](double a, double b)
             { return a * b; }),
    Operator("/", 4, LTR, [](double a, double b)
             { return a / b; }),
    Operator("^", 5, LTR, [](double a, double b)
             { return pow(a, b); }),
    Operator("sin", 5, NONE, [](double a, double b)
             { return sin(a); }),
    Operator("cos", 5, NONE, [](double a, double b)
             { return cos(a); }),
    Operator("tan", 5, NONE, [](double a, double b)
             { return tan(a); }),
    Operator("sqrt", 5, NONE, [](double a, double b)
             { return sqrt(a); }),
    Operator("log", 5, NONE, [](double a, double b)
             { return log(a); }),
    Operator("(", 5, NONE, [](double a, double b)
             { return 0.0; }),
    Operator(")", 5, NONE, [](double a, double b)
             { return 0.0; }),
};

class Token
{
private:
    Type type;
    double value;
    Operator op;

public:
    Token();
    Token(Type _type, double _value);
    Token(Type _type, Operator _op);
    friend class Expression;
};

Token::Token()
{
    type = NUM;
    value = 0;
}

Token::Token(Type _type, double _value)
{
    type = _type;
    value = _value;
}

Token::Token(Type _type, Operator _op)
{
    type = _type;
    op = _op;
}

bool isOp(string s, int i, Operator &op)
{
    return s.substr(i, op.op.length()) == op.op;
}

class Expression
{
public:
    Expression();
    void input();
    void eval();
    void partial_eval();

private:
    string expr;
    stack<Token> operands;
    stack<Token> operators;
};

Expression::Expression()
{
    expr = "";
}

void Expression::input()
{
    getline(cin, expr);
    // regex to detect log_{base}(number), capture base and number
    regex log_regex("log_\\{([0-9]+)\\}\\(([0-9]+)\\)");
    expr = regex_replace(expr, log_regex, "(log($2)/log($1))"); // normalize log, replace with log(number)/log(base)
}

void Expression::eval()
{
    bool unary = true;
    for (int i = 0; i < expr.size(); i++)
    {
        // If the current character is a digit or a period, parse the number and push it onto the operands stack
        if (isdigit(expr[i]) || expr[i] == '.')
        {
            char *endptr;
            double num = strtod(&expr[i], &endptr);
            i += endptr - &expr[i] - 1;
            operands.push(Token(NUM, num));
            unary = false;
        }
        else
        {
            // check if its - and if it is unary
            if (expr[i] == '-' && unary)
            {
                operators.push(Token(OP, opdef[2]));
            }
            else if (expr[i] == ')')
            {
                while (operators.top().op.op != "(")
                {
                    partial_eval();
                }
                operators.pop();
                unary = false;
            }
            else
            {
                // check if it is an operator
                for (int j = 0; j < sizeof(opdef) / sizeof(opdef[0]); j++)
                {
                    if (isOp(expr, i, opdef[j]))
                    {
                        while (!operators.empty() && opdef[j].precedence < operators.top().op.precedence && operators.top().op.op != "(")
                        {
                            partial_eval();
                        }

                        operators.push(Token(OP, opdef[j]));
                        i += opdef[j].op.length() - 1;
                        unary = true;
                        break;
                    }
                }
            }
        }
    }

    while (!operators.empty())
    {
        partial_eval();
    }
    // print the result
    if (!operands.empty())
        cout << operands.top().value << endl;
}

void Expression::partial_eval()
{
    Token op = operators.top();
    operators.pop();

    if (op.op.associativity == NONE)
    {
        Token op1 = operands.top();
        operands.pop();
        // cout << "[EVAL]: " << op.op.op << " " << op1.value << "=" << op.op.func(op1.value, 0) << endl;
        operands.push(Token(NUM, op.op.func(op1.value, 0)));
        return;
    }

    Token op2 = operands.top();
    operands.pop();
    Token op1 = operands.top();
    operands.pop();
    // cout << "[EVAL]: " << op1.value << " " << op.op.op << " " << op2.value << "=" << op.op.func(op1.value, op2.value) << endl;
    operands.push(Token(NUM, op.op.func(op1.value, op2.value)));
}

int main()
{ // DO NOT CHANGE MAIN!!
    Expression exp1;
    exp1.input();
    exp1.eval();
    return 0;
}