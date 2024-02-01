#ifndef LEXER159535
#define LEXER159535

#include <cstdlib>
#include <string>
#include <deque>
#include <queue>
#include <set>

#include "token.h"

/**
 * @brief Divides math expression into CTokens, which are representing numbers and operatos
 *
 */
class CLexer
{
public:
    /**
     * @brief Construct a new CLexer object
     *
     * @param expr mathematical expression, which is supposed to be partitioned
     * @param var map of variables and their values
     */
    CLexer(string expr, const map<string, CNumPtr> &var);
    CLexer(const CLexer &x) = delete;
    CLexer &operator=(const CLexer &x) = delete;
    /**
     * @brief Destroy the CLexer object
     *
     */
    ~CLexer();
    /**
     * @brief Returns queue of CTokens - lexed expression given in constructor
     *
     * @return queue<CToken> queue of CTokens - lexed math expression
     */
    queue<CToken> get() const;

private:
    /**
     * @brief Decides if the given token is expected
     *
     * Based on the previous tokens stored in m_tokens decides if the given token in parametr is expected. If not returns false.
     *
     * @param token the token for which is being decided if it is expected or not
     * @return true given token is expected
     * @return false given token is not expected
     */
    bool isExpected(CToken token);
    /**
     * @brief Get the Number object from given string.
     *
     * If there is not a number exception logic_error is thrown.
     *
     * @param str string in which is searched for a number
     * @param size used as output parametr, writes the size of the read number in the given string
     * @return number which was found in the given string str
     */
    static number getNumber(const string &str, size_t &size);
    /**
     * @brief Get the next Token object from expression m_expr
     *
     * @return CToken found token
     */
    CToken getToken();
    /**
     * @brief Get Token - number
     *
     * In the given string is a expected a variable. Recognizes the ID, finds it in the provided map of variables and returns Token representing the actual value of the variable.
     * If there is not a variable exception logic_error is thrown.
     *
     * @return CToken token representing the actual value of the variable
     */
    CToken getVar();

    /**
     * @brief given math expression, which is supposed to be lexed
     *
     */
    string m_expr;
    /**
     * @brief actual possition when lexing the expression
     *
     */
    size_t m_pos;
    /**
     * @brief Tokens created from the expression
     *
     */
    deque<CToken> m_tokens;
    /**
     * @brief const reference to the given map of variables
     *
     */
    const map<string, CNumPtr> &m_variables;
};

#endif