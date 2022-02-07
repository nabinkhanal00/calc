
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

bool isBrackets(char op) {
	if (op == '(' || op == ')' || op == '[' || op == ']' || op == '{' ||
	    op == '}') {
		return true;
	}
	return false;
}
bool isOperator(char op) {
	if (op == '/' || op == '*' || op == '+' || op == '-' || op == '^' ||
	    op == '!' || op == '@' || op == '#' || op == '(' || op == ')' ||
	    op == '[' || op == ']' || op == '{' || op == '}') {
		return true;
	}
	return false;
}

bool isBrackets(std::string op) {
	if (op == "(" || op == ")" || op == "{" || op == "}" || op == "[" ||
	    op == "]") {
		return true;
	}
	return false;
}
bool isOperator(std::string op) {
	if (op == "/" || op == "*" || op == "+" || op == "-" || op == "^" ||
	    op == "!" || op == "@" || op == "#" || op == "(" || op == ")" ||
	    op == "{" || op == "}" || op == "[" || op == "]") {
		return true;
	}
	return false;
}

std::vector<std::string> split(std::string expression) {
	std::vector<std::string> e;
	std::cout << "The expression is " << expression << std::endl;
	std::string str = "";
	for (auto c : expression) {
		if (c == ' ') {
			continue;
		}
		if (isOperator(c)) {
			if (str != "") {
				e.push_back(str);
			}
			e.push_back(std::string(1, c));
			str = "";
		} else {
			str += c;
		}
	}
	if (str != "") {
		e.push_back(str);
	}
	return e;
}

char m(char c) {
	if (c == ')') {
		return '(';
	} else if (c == '}') {
		return '{';
	} else if (c == ']') {
		return '[';
	}
	return '\0';
}

bool isValid(std::string expression) {
	std::stack<char> s;
	for (auto i : expression) {
		if (i == '{' || i == '[' || i == '(') {
			s.push(i);
		} else if (i == ')' || i == '}' || i == ']') {
			if (s.empty()) {
				return false;
			}
			char top = s.top();
			s.pop();
			if (top != m(i)) {
				return false;
			}
		}
	}
	if (s.empty()) {
		return true;
	}
	return false;
}

std::vector<std::string> infixToPostfix(std::string expression) {
	std::map<std::string, std::string> bPair;
	bPair[")"] = "(";
	bPair["}"] = "{";
	bPair["]"] = "[";

	std::map<std::string, int> priority;
	priority["-"] = 0;
	priority["+"] = 0;
	priority["/"] = 1;
	priority["*"] = 1;
	priority["^"] = 2;
	priority["!"] = 3;
	priority["@"] = 3;
	priority["#"] = 3;
	if (!isValid(expression)) {
		std::cout << "Invalid expression" << std::endl;
	}
	std::vector<std::string> infix = split(expression);
	bool isPreviousOperator = true;
	std::vector<std::string> postfix;
	std::stack<std::string> s;
	for (auto i : infix) {
		if (!isOperator(i)) {
			postfix.push_back(i);
			isPreviousOperator = false;
		} else {
			if (i == "(" || i == "{" || i == "[") {
				s.push(i);
			} else if (i == ")" || i == "}" || i == "]") {
				while (s.top() != bPair[i]) {
					postfix.push_back(s.top());
					s.pop();
				}
				s.pop();
			} else {
				if (isPreviousOperator) {
					if (i == "+" || i == "-" || i == "!" || i == "@" ||
					    i == "#") {
						postfix.push_back("0");
					} else {
						std::cout << "Error: invalid unary operator"
						          << std::endl;
						exit(1);
					}
				}
				if (s.empty() || s.top() == "(" || s.top() == "{" ||
				    s.top() == "[") {
					s.push(i);
				} else {

					while (!s.empty() && s.top() != "(" && s.top() != "{" &&
					       s.top() != "[" && priority[i] <= priority[s.top()]) {
						if (i == "^" && s.top() == "^") {
							break;
						}
						std::string top = s.top();
						postfix.push_back(top);
						s.pop();
					}
					s.push(i);
				}
				isPreviousOperator = true;
			}
		}
	}
	while (!s.empty()) {
		postfix.push_back(s.top());
		s.pop();
	}
	return postfix;
}
std::string eval(std::string first, std::string second, std::string op) {
	double f = std::stof(first);
	double s = std::stof(second);
	double result;
	if (op == "+") {
		result = s + f;
	} else if (op == "-") {
		result = s - f;
	} else if (op == "*") {
		result = f * s;
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

double evalPostfix(std::vector<std::string> postfix) {
	std::stack<std::string> s;
	for (auto i : postfix) {
		if (!isOperator(i)) {
			s.push(i);
		} else {
			std::string first = s.top();
			s.pop();
			if (!s.empty()) {
				std::string second = s.top();
				s.pop();
				std::string evaluatedString = eval(first, second, i);
				s.push(evaluatedString);
			} else {
				s.push(first);
			}
		}
	}
	return std::stof(s.top());
}

int main(int argc, char *argv[]) {
	// ! for sin
	// @ for cos
	// # for tan
	std::string expression = "#(0.78)";
	auto pf = infixToPostfix(expression);
	for (auto i : pf) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	auto result = evalPostfix(pf);
	std::cout << result << std::endl;
}
