#ifndef AST542365
#define AST542365

#include <cstdlib>
#include <string>
#include <queue>
#include <iostream>

#include "node.h"
#include "../token.h"

/**
 * @brief Represents abstract syntax tree of mathematical expression.
 *
 * Creates AST from given queue of parsed CTokens. CTokens must be in postfix notation.
 */
class CTree
{
public:
    /**
     * @brief Construct a new CTree object
     *
     * Constrcut AST from given CTokens in queue in postfix notation.
     *
     * @param expr queue of given CTokens - must be in postfix notation
     */
    CTree(queue<CToken> expr);
    CTree(const CTree &x) = delete;
    CTree &operator=(const CTree &x) = delete;
    /**
     * @brief Destroy the CTree object
     *
     */
    ~CTree();
    /**
     * @brief Evaluates the expression
     *
     * @return number result
     */
    number evaluate() const;

private:
    /**
     * @brief Root of the abstract syntax tree
     */
    CNodePtr m_root;
};

#endif