/**
 * @file Assignment3.cpp
 * @author Chew Tzi Hwee (chewtzihwee@gmail.com)
 * \brief Assignment #3 - Evaluating Mathematical Epressions (https://acm.cs.nthu.edu.tw/problem/13797/)
 * @version 0.1
 * \date 2023-01-08
 *
 * @copyright Copyright (c) 2023
 *
 * \note Compile with -std=c++11 or higher, the code is formatted with Google's Coding Guidelines
 */
#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

/* Enum for Token Type*/
enum Type {
    NUM,
    OP,
};

/* Enum for Associativity Type*/
enum assoc {
    ASSOC, // for binary operators
    NONE  // for unary operators
};

/**
 * Defines an operator and its properties, including precedence and associativity
 * and a pointer to the function that performs the operation
 *
 * Example:
 *     For op = "+", precedence = 1, associativity = ASSOC
 *     Operator("+", 1, ASSOC, [](double a, double b) { return a + b; })
 *
 * To call the given func, use the following syntax:
 *    double ans = op.func(a, b)
 */
class Operator {
   private:
    /* name used to check for operator within the expression */
    string name;
    int precedence;
    assoc associativity;
    /** 
     * func is ptr to defined function, is nullptr if not required. 
     * if associativity is NONE, func is called with only one argument, the second = 0 but should be ignored.
     **/
    double (*func)(double x, double y);

   public:
    Operator();
    Operator(string _op, int _precedence, assoc _associativity,
             double (*func)(double, double));
    friend bool isOp(string s, int i, Operator &op);
    friend class Expression;
};

Operator::Operator() {
    name = "";
    precedence = 0;
    associativity = NONE;
    func = nullptr;
}

Operator::Operator(string _op, int _precedence, assoc _associativity,
                   double (*_func)(double, double)) {
    name = _op;
    precedence = _precedence;
    associativity = _associativity;
    func = _func;
}

/**
 * Array of implemented operators, makes it easier to add new operators
 * Example:
 *    if you want to add a new operator, say "mod", with precedence 2, associativity ASSOC
 *    add the following line to the array:
 *    Operator("mod", 2, ASSOC, [](double a, double b) { return a % b; })
 */
Operator opdef[] = {
    /* Operator(name, precedence, associativity, func) */
    Operator("+", 1, ASSOC, [](double a, double b) { return a + b; }),
    Operator("-", 1, ASSOC, [](double a, double b) { return a - b; }),
    Operator("-", 2, NONE, [](double a, double b) { return -a; }),
    Operator("*", 3, ASSOC, [](double a, double b) { return a * b; }),
    Operator("/", 4, ASSOC, [](double a, double b) { return a / b; }),
    Operator("^", 5, ASSOC, [](double a, double b) { return pow(a, b); }),
    Operator("sin", 5, NONE, [](double a, double b) { return sin(a); }),
    Operator("cos", 5, NONE, [](double a, double b) { return cos(a); }),
    Operator("tan", 5, NONE, [](double a, double b) { return tan(a); }),
    Operator("sqrt", 5, NONE, [](double a, double b) { return sqrt(a); }),
    Operator("log", 5, NONE, [](double a, double b) { return log(a); }),
    Operator("(", 5, NONE, /* Empty Function */ nullptr),
    Operator(")", 5, NONE, /* Empty Function */ nullptr),
};

/**
 * Defines a Token, which can be either a number or an operator
 *
 * Example:
 *     Token(NUM, 3.14) is a number token with value 3.14
 *     Token(OP, Operator("+", 1, ASSOC, [](double a, double b) { return a + b; })) is an operator token with value "+"
 */
class Token {
   private:
    Type type;

    /* value is either the number or the operator */
    double value;
    Operator op;

   public:
    Token();
    Token(Type _type, double _value);
    Token(Type _type, Operator _op);
    friend class Expression;
};

/**
 * Construct a new Token:: Token object
 * Default constructor creates a number token with value 0
 */
Token::Token() {
    type = NUM;
    value = 0;
}

/**
 * Construct a new Token:: Token object
 * Constructs a number token with double _value
 */
Token::Token(Type _type, double _value) {
    type = _type;
    value = _value;
}

/**
 * Construct a new Token:: Token object
 * Constructs an operator token with Operator _op
 */
Token::Token(Type _type, Operator _op) {
    type = _type;
    op = _op;
}

/**
 * \brief           Checks if the string s starting at index i is the same as the operator op
 *
 * \param[in] s:    string to check
 * \param[in] i:    index to start checking
 * \param[in] op:   operator to check
 * \return bool
 */
bool isOp(string s, int i, Operator &op) {
    return s.substr(i, op.name.length()) == op.name;
}

/**
 * Contains the expression and the stacks for operands and operators
 * Example:
 *    Expression e;
 *    e.input();
 *    e.eval();
 */
class Expression {
   public:
    Expression();
    void input();
    void eval();

   private:
    string expr;
    stack<Token> operands;
    stack<Token> operators;
    void partial_eval();
};

/**
 * Construct a new Expression:: Expression object
 * Default constructor creates an empty expression
 */
Expression::Expression() { expr = ""; }

/**
 * \brief           Reads the expression from the user
 *
 * \return void
 */
void Expression::input() {
    getline(cin, expr);
    // regex to detect log_{base}(number), capture base and number
    regex log_regex("log_\\{([0-9]+)\\}\\(([0-9]+)\\)");
    expr = regex_replace(expr, log_regex,
                         "(log($2)/log($1))");  // normalize log, replace with
                                                // log(number)/log(base)
}

/**
 * \brief           Evaluates the expression
 *
 * \return void
 */
void Expression::eval() {
    bool unary = true;
    for (int i = 0; i < expr.size(); i++) {
        // If the current character is a digit or a period, parse the number and
        // push it onto the operands stack
        if (isdigit(expr[i]) || expr[i] == '.') {
            // Use strtod to parse the number, then store the end pointer in endptr
            char *endptr;
            double num = strtod(&expr[i], &endptr);

            // Move i to the end of the number
            i += endptr - &expr[i] - 1;

            operands.push(Token(NUM, num));

            // Since we just pushed a number, the next token cannot be unary
            unary = false;
        } else {
            if (expr[i] == '-' && unary) {  // Check if its '-' and if it is unary
                operators.push(Token(OP, opdef[2]));
            } else if (expr[i] == ')') {  // Check if its ')'
                // if the top operator is not (, evaluate it
                while (operators.top().op.name != "(") {
                    partial_eval();
                }
                operators.pop();

                // Since we just pushed a number, the next token cannot be unary
                unary = false;
            } else {
                // check if it is an operator by looping through the opdef array
                for (int j = 0; j < sizeof(opdef) / sizeof(opdef[0]); j++) {
                    if (isOp(expr, i, opdef[j])) {
                        // Check if the current top operator has higher precedence, if it does, evaluate it
                        while (!operators.empty() &&
                               opdef[j].precedence < operators.top().op.precedence &&
                               operators.top().op.name != "(") {
                            partial_eval();
                        }
                        operators.push(Token(OP, opdef[j]));

                        // Move i to the end of the operator
                        i += opdef[j].name.length() - 1;

                        // Since we just pushed an operator, the next token can be unary
                        unary = true;
                        break;
                    }
                }
            }
        }
    }

    // Evaluate the remaining operators
    while (!operators.empty()) {
        partial_eval();
    }
    // Print the result
    if (!operands.empty()) cout << operands.top().value << endl;
}

/**
 * \brief           Only evaluates the top operator on the operators stack
 *
 * \return void
 */
void Expression::partial_eval() {
    Token operator_token = operators.top();
    operators.pop();

    // If the operator is not associative, we only need to pop one operand
    if (operator_token.op.associativity == NONE) {
        Token op1 = operands.top();
        operands.pop();
        // Evaluate the operator and push the result onto the operands stack
        operands.push(Token(NUM, operator_token.op.func(op1.value, 0)));
        return;
    }
    else {
        // If the operator is associative, we need to pop two operands
        Token op2 = operands.top();
        operands.pop();
        Token op1 = operands.top();
        operands.pop();
        // Evaluate the operator and push the result onto the operands stack
        operands.push(Token(NUM, operator_token.op.func(op1.value, op2.value)));
    }
}

int main() {  // DO NOT CHANGE MAIN!!
    Expression exp1;
    exp1.input();
    exp1.eval();
    return 0;
}