#include <cstdlib>
#include <string>
#include <queue>
#include <stack>
#include <iostream>

#include "node.h"
#include "ast.h"
#include "../token.h"

CTree::CTree(queue<CToken> q)
    : m_root(nullptr)
{
    if (q.empty())
        return;
    stack<CNodePtr> s;

    // creating AST from given queue of tokens:
    while (!q.empty())
    {
        if (q.front().isNumber())
        {
            s.emplace(q.front().getNode()); // numbers placing to a stack
        }
        else if (q.front().isOperator()) // from operators creating CNodes with numbers from the stack
        {
            if (s.empty())
                throw logic_error("invalid expression: invalid number of operands");

            CNodePtr right(s.top()); // right operand
            s.pop();

            if (s.empty())
                throw logic_error("invalid expression: invalid number of operands");
            CNodePtr left(s.top()); // left operand of the operator
            s.pop();
            CNodePtr tmp(q.front().getNode(left, right));

            s.emplace(tmp);
        }

        q.pop();
    }
    if (!q.empty())
        throw logic_error("invalid expression: invalid number of operands");
    // check if on stack is only one node
    swap(m_root, s.top());
    s.pop();
    if (!s.empty())
        throw logic_error("invalid expression: invalid number of operands");
}

CTree::~CTree() {}

number CTree::evaluate() const
{
    if (!m_root)
        throw std::logic_error("invalid expression");
    return m_root->evaluate();
}
