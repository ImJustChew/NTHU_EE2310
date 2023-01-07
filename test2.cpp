#include <stack>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


// Returns the precedence of the given operator
int precedence(const std::string& op) {
  if (op == "sin" || op == "cos" || op == "tan" || op == "log" || op == "sqrt") {
    return 3;
  } else if (op == "*" || op == "/") {
    return 2;
  } else if (op == "+" || op == "-") {
    return 1;
  } else {
    return 0;
  }
}

class Token {
public:
  // Enum class for the different types of tokens
  enum class Type {
    NUMBER,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN,
  };

  // Constructor for a number token
  Token(double value) : type_(Type::NUMBER), value_(value) {}
  // Constructor for an operator token
  Token(const string& op) : type_(Type::OPERATOR), op_(op) {}
  // Constructor for a left parenthesis token
  Token() : type_(Type::LEFT_PAREN) {}
  // Constructor for a right parenthesis token
  Token(Type right_paren) : type_(Type::RIGHT_PAREN) {}

  // Accessor for the token type
  Type type() const { return type_; }
  // Accessor for the number value (only valid if type is NUMBER)
  double value() const { return value_; }
  // Accessor for the operator value (only valid if type is OPERATOR)
  const string& op() const { return op_; }

private:
  Type type_;
  double value_;
  string op_;
};

class Expression {
public:
  // Reads an expression from standard input
  void input() {
    string input;
    getline(cin, input);
    tokens_ = tokenize(input);
  }

  // Evaluates the expression and prints the result to standard output
  void eval() {
    stack<double> operands;
    stack<Token> operators;

    for (const Token& token : tokens_) {
      if (token.type() == Token::Type::NUMBER) {
        operands.push(token.value());
      } else if (token.type() == Token::Type::OPERATOR) {
        while (!operators.empty() && precedence(operators.top().op()) >= precedence(token.op())) {
          eval_operator(operands, operators);
        }
        operators.push(token);
      } else if (token.type() == Token::Type::LEFT_PAREN) {
        operators.push(token);
      } else if (token.type() == Token::Type::RIGHT_PAREN) {
        while (operators.top().type() != Token::Type::LEFT_PAREN) {
          eval_operator(operands, operators);
        }
        operators.pop();
      }
    }

    while (!operators.empty()) {
      eval_operator(operands, operators);
    }

    cout << operands.top() << endl;
  }

private:
    vector<Token> tokens_;
    // Tokenizes the input string
    vector<Token> tokenize(const string& input) {
        vector<Token> tokens;
        stringstream ss(input);
        string buffer;
        while (ss >> buffer) {
            if (buffer == "(") {
            tokens.emplace_back();
            } else if (buffer == ")") {
            tokens.emplace_back(Token::Type::RIGHT_PAREN);
            } else if (buffer == "sin" || buffer == "cos" || buffer == "tan" || buffer == "log" || buffer == "sqrt") {
            tokens.emplace_back(buffer);
            } else if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            tokens.emplace_back(stod(buffer));
            } else {
            tokens.emplace_back(buffer);
            }
        }
        return tokens;
    }

    void eval_operator(stack<double>& operands, stack<Token>& operators) {
        double right = operands.top();
        operands.pop();
        double left = operands.top();
        operands.pop();
        const string& op = operators.top().op();
        operators.pop();

        if (op == "+") {
            operands.push(left + right);
        } else if (op == "-") {
            operands.push(left - right);
        } else if (op == "*") {
            operands.push(left * right);
        } else if (op == "/") {
            operands.push(left / right);
        } else if (op == "sin") {
            operands.push(sin(right));
        } else if (op == "cos") {
            operands.push(cos(right));
        } else if (op == "tan") {
            operands.push(tan(right));
        } else if (op == "log") {
            operands.push(log(right));
        } else if (op == "sqrt") {
            operands.push(sqrt(right));
        }
    }
};
int main() {
  Expression exp1;
  exp1.input();
  exp1.eval();
  return 0;
}
