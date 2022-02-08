#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Calculator.h"

inline bool Calculator::isvariablechar(const char c) {
	return isalpha(c) || c == '_';
}
// ! : sin
// @ : cos
// # : tan
std::map<std::string, int> Calculator::operator_precedence = {
    {"(", -1}, {"<<", 0}, {">>", 0}, {"+", 1}, {"-", 1}, {"*", 2},
    {"/", 2},  {"^", 3},  {"!", 4},  {"@", 4}, {"#", 4}};

std::vector<std::string> Calculator::find_variables(const char *_expr) {

	std::vector<std::string> variables;

	// while an expression is not read completely
	while (*_expr) {

		// find a block of string : variable
		// that can be later replaced by a value
		if (isvariablechar(*_expr)) {
			std::stringstream ss;
			ss << *_expr;
			++_expr;
			while (isvariablechar(*_expr)) {
				ss << *_expr;
				++_expr;
			}
			std::string key = ss.str();
			variables.push_back(key);
		} else {
			_expr++;
		}
	}
	return variables;
};

TokenQueue_t Calculator::to_rpn(const char *_expr,
                                std::map<std::string, double> *_vars) {
	TokenQueue_t rpnQueue;

	std::stack<std::string> operatorStack;

	bool lastTokenWasOp = true;

	while (*_expr && isspace(*_expr)) {
		++_expr;
	}
	while (*_expr) {
		if (isdigit(*_expr)) {
			char *nextChar = 0;
			double digit = strtod(_expr, &nextChar);
			rpnQueue.push(new Token<double>(digit));
			_expr = nextChar;
			lastTokenWasOp = false;
		} else if (isvariablechar(*_expr)) {
			if (!_vars) {
				throw std::domain_error(
				    "Detected variable, but the variable map is null.");
			}

			std::stringstream ss;
			ss << *_expr;
			++_expr;
			while (isvariablechar(*_expr)) {
				ss << *_expr;
				++_expr;
			}
			std::string key = ss.str();
			std::map<std::string, double>::iterator it = _vars->find(key);
			if (it == _vars->end()) {
				throw std::domain_error("Unable to find the variable '" + key +
				                        "'.");
			}
			double val = _vars->find(key)->second;
			rpnQueue.push(new Token<double>(val));
			lastTokenWasOp = false;
		} else {
			switch (*_expr) {
			case '(':
				operatorStack.push("(");
				++_expr;
				break;
			case ')':
				while (operatorStack.top().compare("(")) {
					rpnQueue.push(new Token<std::string>(operatorStack.top()));
					operatorStack.pop();
				}
				operatorStack.pop();
				++_expr;
				break;
			default: {
				// it means the token is an operator
				std::stringstream ss;
				ss << *_expr;
				++_expr;
				while (*_expr && !isspace(*_expr) && !isdigit(*_expr) &&
				       !isvariablechar(*_expr) && *_expr != '(' &&
				       *_expr != ')' && *_expr != '!' && *_expr != '@' &&
				       *_expr != '#' && *_expr != '+' && *_expr != '-') {
					ss << *_expr;
					++_expr;
				}
				ss.clear();
				std::string str;
				ss >> str;
				if (lastTokenWasOp) {
					if (!str.compare("-") || !str.compare("+") ||
					    !str.compare("!") || !str.compare("@") ||
					    !!str.compare("#")) {
						rpnQueue.push(new Token<double>(0));
					} else {
						throw std::domain_error(
						    "Unrecognized unary operator: '" + str + "'.");
					}
				}
				while (!operatorStack.empty() &&
				       operator_precedence[str] <=
				           operator_precedence[operatorStack.top()]) {
					if (operatorStack.top() == "^" && str == "^") {
						break;
					}
					rpnQueue.push(new Token<std::string>(operatorStack.top()));
					operatorStack.pop();
				}

				operatorStack.push(str);
				lastTokenWasOp = true;
				break;
			}
			}
		}
	}
	while (!operatorStack.empty()) {
		rpnQueue.push(new Token<std::string>(operatorStack.top()));
		operatorStack.pop();
	}
	return rpnQueue;
}

double Calculator::calculate(const char *_expr,
                             std::map<std::string, double> *_vars) {
	TokenQueue_t rpn = to_rpn(_expr, _vars);
	std::stack<double> evaluation;
	while (!rpn.empty()) {
		TokenBase *base = rpn.front();
		rpn.pop();
		Token<std::string> *strTok = dynamic_cast<Token<std::string> *>(base);
		Token<double> *doubleTok = dynamic_cast<Token<double> *>(base);

		if (strTok) {
			std::string str = strTok->val;
			if (evaluation.size() < 2) {
				throw std::domain_error("Invalid equation");
			}
			double right = evaluation.top();
			evaluation.pop();
			double left = evaluation.top();
			evaluation.pop();
			if (!str.compare("+")) {
				evaluation.push(left + right);
			} else if (!str.compare("-")) {
				evaluation.push(left - right);
			} else if (!str.compare("/")) {
				evaluation.push(left / right);
			} else if (!str.compare("*")) {
				evaluation.push(left * right);
			} else if (!str.compare("^")) {
				evaluation.push(pow(left, right));
			} else if (!str.compare("!")) {
				evaluation.push(sin(right));
			} else if (!str.compare("@")) {
				evaluation.push(cos(right));
			} else if (!str.compare("#")) {
				evaluation.push(tan(right));
			} else {
				throw std::domain_error("Unknown operator: '" + str + "'.");
			}
		} else if (doubleTok) {
			evaluation.push(doubleTok->val);
		} else {
			throw std::domain_error("Invalid token.");
		}
		delete base;
	}
	return evaluation.top();
}

int main() {
	try {
		std::map<std::string, double> m;
		const char *expression = "-1+2";
		auto vars = Calculator::find_variables(expression);
		for (auto i : vars) {
			std::cout << "Enter the value for " << i << " : ";
			std::cin >> m[i];
		}
		std::cout << Calculator::calculate(expression, &m) << std::endl;
	} catch (std::domain_error e) {
		std::cout << e.what() << std::endl;
	}
}
