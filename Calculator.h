#pragma once

#include <map>
#include <queue>
#include <stack>
#include <string>

// base class for every tokens
struct TokenBase {
	virtual ~TokenBase() {}
};

// a token is an operator or operand
template <typename T> struct Token : public TokenBase {
	T val;
	Token(T t) : val(t) {}
};

// queue of tokens
typedef std::queue<TokenBase *> TokenQueue_t;

class Calculator {
  public:
	static double calculate(const char *_expr,
	                        std::map<std::string, double> *_vars = 0);

	static std::vector<std::string> find_variables(const char *expr);

  private:
	static TokenQueue_t to_rpn(const char *expr,
	                           std::map<std::string, double> *_vars);
	static std::map<std::string, int> operator_precedence;

	static bool isvariablechar(const char c);
};