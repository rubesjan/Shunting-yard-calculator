#include <cstdlib>
#include <queue>
#include <string>
#include <map>

#include "lexer.h"
#include "token.h"
#include "./num/num.h"

CLexer::~CLexer() {}

CLexer::CLexer(string expr, const map<string, CNumPtr> &var)
    : m_expr(move(expr)), m_pos(0), m_tokens{}, m_variables(var)
{
    // make tokens from the expresion
    CToken tmp(getToken());
    while (!tmp.isEof())
    {
        m_tokens.emplace_back(move(tmp));
        tmp = getToken();
    }
}

number CLexer::getNumber(const string &str, size_t &size)
{
    size_t i(0);

    while (isspace(str[i]))
        i++;

    if (str[i] == '-' || str[i] == '+')
    {
        i++;
    }

    bool decimal = false;
    while (isdigit(str[i]) || str[i] == '.')
    {
        if (str[i] == '.' && !decimal)
            decimal = true;
        else if (str[i] == '.' && decimal)
            throw logic_error("invalid expression: invalid number - two decimal points");
        i++;
    }
    size = i;
    auto tmp = str.substr(0, i);
    return getCNum(move(tmp));
}

bool CLexer::isExpected(CToken token)
{
    if (token.isOperator() && (m_tokens.empty() || !(!m_tokens.empty() && (m_tokens.back().isNumber() || m_tokens.back().isRParen()))))
        return false;
    else if (token.isLParen() && !((!m_tokens.empty() && (m_tokens.back().isOperator() || m_tokens.back().isLParen())) || m_tokens.empty()))
        return false;
    else if (token.isRParen() && (m_tokens.empty() || !(!m_tokens.empty() && (m_tokens.back().isNumber() || m_tokens.back().isRParen()))))
        return false;
    return true;
}

CToken CLexer::getToken()
{
    if (m_pos >= m_expr.size())
        return CToken(CToken::CType::eof);

    while (isspace(m_expr[m_pos]))
        m_pos++;

    if (m_pos >= m_expr.size())
        return CToken(CToken::CType::eof);

    char c = m_expr[m_pos];

    // operators
    switch (c)
    {
    case '+':
    {
        CToken tmp(CToken::CType::plus);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case '-':
    {
        CToken tmp(CToken::CType::minus);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case '*':
    {
        CToken tmp(CToken::CType::multiplicate);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case '(':
    {
        CToken tmp(CToken::CType::lparen);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case ')':
    {
        CToken tmp(CToken::CType::rparen);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case '/':
    {
        CToken tmp(CToken::CType::divide);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case '%':
    {
        CToken tmp(CToken::CType::modulus);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    case '^':
    {
        CToken tmp(CToken::CType::pow);
        if (!isExpected(tmp))
            break;
        m_pos++;
        return tmp;
    }
    }

    // if number is expected
    if ((isdigit(m_expr[m_pos]) || ((m_expr[m_pos] == '+' || m_expr[m_pos] == '-') && (m_tokens.empty() || (!m_tokens.empty() && !m_tokens.back().isOperator())))) && (m_tokens.empty() || (!m_tokens.empty() && (m_tokens.back().isOperator() || m_tokens.back().isLParen()))))
    {
        size_t size = 0;
        number num = getNumber(m_expr.data() + m_pos, size);
        m_pos += size;
        return CToken(CToken::CType::number, num);
    };
    return this->getVar();
}

CToken CLexer::getVar()
{
    if (isalpha(m_expr[m_pos]))
    {
        size_t i(m_pos);
        while (isalpha(m_expr[i]))
            i++;
        string id = m_expr.substr(m_pos, i - m_pos);

        // find it
        auto var = m_variables.find(id);
        if (var != m_variables.end())
        {
            m_pos += i - m_pos;
            return CToken(CToken::CType::number, var->second);
        }

        throw logic_error("invalid expression: invalid indentifier \""s + id + "\""s);
    }
    else // throw exception with right description
    {
        switch (m_expr[m_pos])
        {
        case '+':
            throw logic_error("invalid expression: expected number got \"+\"");
        case '-':
            throw logic_error("invalid expression: expected number got \"-\"");
        case '*':
            throw logic_error("invalid expression: expected number got \"*\"");
        case '/':
            throw logic_error("invalid expression: expected number got \"/\"");
        case '%':
            throw logic_error("invalid expression: expected number got \"%\"");
        case '^':
            throw logic_error("invalid expression: expected number got \"^\"");
        }
    }

    if (isdigit(m_expr[m_pos]))
    {
        size_t size;
        auto num = getNumber(m_expr.data() + m_pos, size);
        throw logic_error("invalid expression: expected operator got number: "s + num->print());
    }

    // invalid character
    throw logic_error("invalid expression: invalid character \""s + (m_expr[m_pos]) + "\""s);
}

queue<CToken> CLexer::get() const
{
    return queue<CToken>(m_tokens);
}