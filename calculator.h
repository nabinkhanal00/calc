#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cctype>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <cmath>
#include <regex>

class Calculator {
  private:
	bool is_operator(char c);
	bool is_unary(char c);
	static std::map<std::string, int> priority_table;
	std::vector<std::string> to_rpn(std::vector<std::string>& expression,
	                                std::map<std::string, double> *m);
	std::vector<std::string> split();
	std::string evaluate(std::vector<std::string>& rpn);
	std::string eval(std::string first, std::string second, std::string op);
    bool isValid(std::string expression);
  public:
	Calculator();
	double calculate(std::map<std::string, double> *m = nullptr);
	std::vector<std::string> expression_history;
	std::vector<std::string> variables;
	double previous_answer;
	std::string calculate_input;
	std::string display_input;
};
#endif // CALCULATOR_H
