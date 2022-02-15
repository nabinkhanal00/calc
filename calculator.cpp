#include "calculator.h"
#include <iostream>

Calculator::Calculator()
    : previous_answer(0), calculate_input(""), display_input("") {}

std::map<std::string, int> Calculator::priority_table = {
    {"(", -1}, {"<<", 0}, {">>", 0}, {"+", 1}, {"-", 1}, {"*", 2},
    {"/", 2},  {"^", 3},  {"!", 4},  {"@", 4}, {"#", 4}};

inline bool Calculator::is_operator(char c) {
	if (c == '/' || c == '*' || c == '^' || is_unary(c)) {
		return true;
	}
	return false;
}

inline bool Calculator::is_unary(char c) {
	if (c == '+' || c == '-' || c == '!' || c == '@' || c == '#') {
		return true;
	}
	return false;
}

std::vector<std::string> find_variables(std::string expression) {
	std::vector<std::string> variables;
	const char *cstr = expression.c_str();
	while (*cstr) {
		std::string var = "";
		while (*cstr && (std::isalpha(*cstr) || *cstr == '_')) {
			var += *cstr;
			cstr++;
		}
		if (var != "") {
			variables.push_back(var);
		}
		cstr++;
	}
	return variables;
}

std::vector<std::string> Calculator::split() {

	// convert to c style string
	// easier to perform strtod function
	const char *expr = calculate_input.c_str();

	// checking if the previous token was an operator
	bool is_previous_operator = true;

	// checking if the previous token was a digit
	bool is_previous_digit = false;

	// total parentheses
	int tp = 0;

	// parentheses during adding
	int pc = 0;

	int ac = 0;

	// to store the result of the splitting
	std::vector<std::string> result;

	// while the expression is not read completely
	while (*expr) {

		// ignore the whitespace
		if (*expr == ' ') {
			expr++;
		}
		// if the given character is a digit [0-9]
		else if (std::isdigit(*expr)) {

			// with the help of strtod function we can extract whole
			// double digit at a time

			// new_expr is for pointing to next character after the double
			// number
			char *new_expr = 0;
			double digit = std::strtod(expr, &new_expr);
			result.push_back(std::to_string(digit));

			// maintaining the booleans
			is_previous_digit = true;
			is_previous_operator = false;

			// changing the expr pointer to the new pointer which points to
			// the character after the double number
			expr = new_expr;

			if (ac > 0 && pc == 0) {
				result.push_back(")");
				ac--;
			}

		}

		// for finding the variables in the
		else if (std::isalpha(*expr)) {
			std::string variable = "";
			while (expr && std::isalpha(*expr)) {
				variable += *expr;
				expr++;
			}
			if (variable != "") {
				result.push_back(variable);
			}
			is_previous_digit = true;
			is_previous_operator = false;
		}

		// putting the brackets as they are
		else if (*expr == '(' || *expr == ')') {
			if (*expr == '(') {
				tp++;
				if (ac > 0) {
					pc++;
				}
			} else {
				tp--;
				if (ac > 0) {
					pc--;
				}
			}
			if (tp < 0) {
				throw std::domain_error("Invalid use of parentheses.");
			}
			result.push_back(std::string(1, *expr));
			expr++;
		}
		// if the scanned character is the operator
		else if (is_operator(*expr)) {
			if (is_previous_operator) {
				// if the previous character was operator and this character
				// is unary add the brackets between them
				if (is_unary(*expr)) {
					if (result.empty() || result.back() != "(") {
						ac++;
						result.push_back("(");
						result.push_back("0");
					}
				} else {
					throw std::domain_error("Invalid expression");
				}
			}
			result.push_back(std::string(1, *expr));
			is_previous_operator = true;
			is_previous_digit = false;
			expr++;
		} else {
			std::string error = "Unknown Operator: ";
			error += *expr;
			throw std::domain_error(error);
		}
	}
	if (ac > 0) {
		result.push_back(")");
		ac--;
	}
	return result;
}

std::vector<std::string>
Calculator::to_rpn(std::vector<std::string> &expression,
                   std::map<std::string, double> *m = nullptr) {

	std::vector<std::string> rpn;

	std::stack<std::string> operator_stack;

	for (auto &token : expression) {

		if (!is_operator(token[0]) && token != "(" && token != ")") {

			if (token[0] >= '0' && token[0] <= '9') {
				rpn.push_back(token);

			} else {
				std::map<std::string, double>::iterator it = m->find(token);
				if (it == m->end()) {
					throw std::domain_error("Unable to find the variable '" +
					                        token + "'.");
				}
				double val = m->find(token)->second;
				rpn.push_back(token);
			}
		} else if (token == "(") {
			operator_stack.push(token);
		} else if (token == ")") {
			try {
				while (operator_stack.top() != "(") {
					rpn.push_back(operator_stack.top());
					operator_stack.pop();
				}
				operator_stack.pop();
			} catch (...) {
				throw std::domain_error("Invalid use of parentheses");
			}
		} else {
			while (!operator_stack.empty() &&
			       priority_table[token] <=
			           priority_table[operator_stack.top()]) {
				if (operator_stack.top() == "^" && token == "^") {
					break;
				}
				rpn.push_back(operator_stack.top());
				operator_stack.pop();
			}
			operator_stack.push(token);
		}
	}
	while (!operator_stack.empty()) {
		rpn.push_back(operator_stack.top());
		operator_stack.pop();
	}
	return rpn;
}

std::string Calculator::eval(std::string first, std::string second,
                             std::string op) {
	double f = std::stof(first);
	double s = std::stof(second);
	double result;
	if (op == "+") {
		result = s + f;
	} else if (op == "-") {
		result = s - f;
	} else if (op == "*") {
		result = s * f;
	} else if (op == "/") {
		result = s / f;
	} else if (op == "^") {
		result = pow(s, f);
	} else if (op == "!") {
		result = sin(f);
	} else if (op == "@") {
		result = cos(f);
	} else if (op == "#") {
		result = tan(f);
	}
	return std::to_string(result);
}

std::string Calculator::evaluate(std::vector<std::string> &rpn) {
	std::stack<std::string> number_stack;
	for (auto &token : rpn) {
		if (token[0] >= '0' && token[0] <= '9') {
			number_stack.push(token);
		} else {
			std::string first = number_stack.top();
			number_stack.pop();
			if (!number_stack.empty()) {
				std::string second = number_stack.top();
				number_stack.pop();
				std::string evaluated_string = eval(first, second, token);
				number_stack.push(evaluated_string);
			} else {
				number_stack.push(first);
			}
		}
	}
	return number_stack.top();
}

double Calculator::calculate(std::map<std::string, double> *m) {
	std::vector<std::string> infix = split();
	std::vector<std::string> rpn = to_rpn(infix, m);
	std::string result = evaluate(rpn);
	return std::stod(result);
}