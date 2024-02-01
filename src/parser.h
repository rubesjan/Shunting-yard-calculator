#ifndef PARSER856535
#define PARSER856535

#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>

#include "token.h"
#include "lexer.h"

using namespace std;

/**
 * @brief Parses and evaluates math expression from given string.
 *
 * Using CLexer, divides expression into CTokens. Then using Shunting-yard algorithm parse the expression from infix notaion into postfix notation.
 * When evaluating creates an abstract syntax tree from postfix notation evaluates the AST.
 *
 */
class CParser
{
public:
    /**
     * @brief Construct a new CParser object from given expression
     *
     * Autimatically creates CLexer object, and stores the expression in tokens in m_tokens.
     * If the expression is invalid exception can be thrown from CLexer.
     *
     * @param expr expression to be parsed
     * @param var variables, that could be used in the expression
     */
    CParser(string expr, const map<string, CNumPtr> &var);
    CParser(const CParser &x) = delete;
    CParser &operator=(const CParser &x) = delete;
    /**
     * @brief Destroy the CParser object
     *
     */
    ~CParser();
    /**
     * @brief Prints actual values of member variables. For debugging purposes only.
     *
     * @param out ostream to which variables are printed
     */
    void print(ostream &out = cout);
    /**
     * @brief Get result of the expression
     *
     * If the expression is invalid exception can be thrown from method "parse".
     *
     * @return number result of the expression
     */
    number evaluate();

private:
    /**
     * @brief Parses the expression. Parsed tokens are stored in a queue.
     *
     * If expression contains unmatched parethesis exception logic_error is thrown.
     *
     */
    void parse();
    /**
     * @brief Clears all member variables including all containers.
     */
    void clear();
    /**
     * @brief Decides if the expression is a "Round" function
     *
     * @param x expression
     * @param var list of variables
     * @return true expression is a Round function
     * @return false expression is not a Round function
     */
    bool isRound(const string &x, const map<string, CNumPtr> &var);
    /**
     * @brief Decides if the expression is a "Factorial" function
     *
     * @param x expression
     * @param var list of variables
     * @return true expression is a Factorial function
     * @return false expression is not a Factorial function
     */
    bool isFactorial(const string &x, const map<string, CNumPtr> &var);
    /**
     * @brief Decides if the expression is a function.
     *
     * If it is a function with wrong syntax exception logic_error is thrown.
     *
     * @param s expression
     * @param f name of the function
     * @param binary if the function should have two operands separated by ','
     * @return 0 - false, expression is not a function
     * @return number - position of the first operand of the function
     */
    static int isFunction(const string &s, const string &f, bool binary = false);

    /**
     * @brief If this expression was already parsed.
     *
     */
    bool m_parsed;
    /**
     * @brief Queue of tokens from CLexer. Only lexed expression not parsed.
     *
     */
    queue<CToken> m_tokens;
    /**
     * @brief Stack used in Shunting-yard algorithm.
     *
     */
    stack<CToken> m_stack;
    /**
     * @brief queue of parsed CTokens in postfix notation.
     *
     */
    queue<CToken> m_queue;
};
#endif