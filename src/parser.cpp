#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <set>

#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "./ast/ast.h"
#include "./num/num.h"

using namespace std;

int CParser::isFunction(const string &s, const string &f, bool binary)
{
    size_t i = 0;
    while (isspace(s[i]))
        ++i;

    if (s.empty() || (i + f.size()) > s.size())
        return 0;

    for (size_t k = 0; k < f.size(); i++, k++)
        if (toupper(s[i]) != toupper(f[k]))
            return 0;

    if (s[i] != '(') // it is a function without left parenthesis
        throw std::logic_error("invalid expression: missing parenthesis in function");

    if (binary && s.find(',') == string::npos)
        throw std::logic_error("invalid expression: missing delimeter \",\" between numbers");

    auto it = s.rbegin();
    while (isspace(*it))
        ++it;

    if (*it != ')') // it is a function without right parenthesis
        throw std::logic_error("invalid expression: missing right parenthesis in function");

    return (i + 1);
}

void CParser::clear()
{
    while (!m_tokens.empty())
        m_tokens.pop();

    while (!m_stack.empty())
        m_stack.pop();

    while (!m_queue.empty())
        m_queue.pop();

    m_parsed = false;
}

bool CParser::isRound(const string &x, const map<string, CNumPtr> &var)
{
    size_t from = isFunction(x, "round", false);
    if (from == 0)
        return false;

    size_t to = x.find(')');
    m_tokens = CLexer(move(x.substr(from, to - from)), var).get(); // lex the expression in parenthesis
    CNumPtr number = this->evaluate();                             // evaluate the expression from parenthesis
    this->clear();
    number = round(number);                               // round the result
    m_tokens.push(CToken(CToken::CType::number, number)); // save the result
    return true;
}

bool CParser::isFactorial(const string &x, const map<string, CNumPtr> &var)
{
    size_t from = isFunction(x, "factorial", false);
    if (from == 0)
        return false;

    size_t to = x.find(')');
    m_tokens = CLexer(move(x.substr(from, to - from)), var).get(); // lex the expression in parenthesis
    CNumPtr number = this->evaluate();                             // evaluate the expression from parenthesis
    this->clear();
    number = factorial(number);                           // factorial the result
    m_tokens.push(CToken(CToken::CType::number, number)); // save the result
    return true;
}

CParser::CParser(string x, const map<string, CNumPtr> &var)
    : m_parsed(false), m_tokens(), m_stack{}, m_queue{}
{
    // search for functions:
    if (this->isRound(x, var) || this->isFactorial(x, var)) // it is a function
        return;

    // not a function
    m_tokens = move(CLexer(move(x), var).get());
}

CParser::~CParser() {}

void CParser::print(ostream &out)
{
    out << "m_tokens: " << endl;
    queue<CToken> tmp(m_tokens);
    bool empty(tmp.empty());
    while (!tmp.empty())
    {
        tmp.front().print(out);
        out << " ";
        tmp.pop();
    }
    if (!empty)
        out << endl;
    out << "parsed: " << endl;
    tmp = m_queue;
    empty = tmp.empty();
    while (!tmp.empty())
    {
        tmp.front().print(out);
        out << " ";
        tmp.pop();
    }
    if (!empty)
        out << endl;
    out << endl;
}

void CParser::parse()
{
    // shunting yard algorithm
    while (!m_tokens.empty())
    {
        CToken x = m_tokens.front();
        m_tokens.pop();
        if (x.isNumber())
        {
            m_queue.emplace(x);
        }
        else if (x.isOperator())
        {
            // check priority, if lower than top of the stack move the operator to queue
            while (!m_stack.empty() && m_stack.top().isOperator() && m_stack.top().priority() >= x.priority())
            {
                m_queue.emplace(m_stack.top());
                m_stack.pop();
            }
            m_stack.emplace(x);
        }
        else if (x.isLParen())
        {
            m_stack.emplace(x);
        }
        else if (x.isRParen())
        {
            // match the left parethesis from stack and move the operators to queue
            while (!m_stack.empty() && !m_stack.top().isLParen())
            {
                m_queue.emplace(m_stack.top());
                m_stack.pop();
            }
            if (!m_stack.empty() && m_stack.top().isLParen())
            {
                m_stack.pop();
            }
            else
            {
                // not matching parenthesis
                throw logic_error("invalid expression: unmatched right parenthesis");
            }
        }
    }
    while (!m_stack.empty())
    {
        if (m_stack.top().isLParen())
            throw logic_error("invalid expression: unmatched left parenthesis");
        m_queue.emplace(m_stack.top());
        m_stack.pop();
    }
    m_parsed = true;
}

number CParser::evaluate()
{
    if (!m_parsed)
        this->parse();

    CTree tmp(m_queue);
    return tmp.evaluate();
}
