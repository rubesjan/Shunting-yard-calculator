#include <cstdlib>
#include <iostream>
#include <cassert>

#include "token.h"
#include "./num/num.h"
#include "./ast/boperator.h"
#include "./ast/plusnode.h"
#include "./ast/minusnode.h"
#include "./ast/multnode.h"
#include "./ast/numnode.h"
#include "./ast/dividenode.h"
#include "./ast/modulusnode.h"
#include "./ast/pownode.h"

using namespace std;

CToken::CToken(const CType type, const number num)
    : m_type{type}, m_n{num} {}

CToken::CToken(const CType type)
    : m_type{type} {}

bool CToken::isOperator() const
{
    if (m_type == CToken::CType::plus || this->m_type == CType::minus || this->m_type == CType::multiplicate || m_type == CType::divide || m_type == CType::modulus || m_type == CType::pow)
        return true;
    return false;
}

bool CToken::isNumber() const
{
    if (m_type == CType::number)
        return true;
    return false;
}

bool CToken::isLParen() const
{
    if (m_type == CType::lparen)
        return true;
    return false;
}

bool CToken::isRParen() const
{
    if (m_type == CType::rparen)
        return true;
    return false;
}

bool CToken::isEof() const
{
    if (m_type == CType::eof)
        return true;
    return false;
}

number CToken::getValue() const
{
    if (m_n.has_value())
        return m_n.value();
    throw logic_error("not a number");
}

void CToken::print(ostream &out) const
{
    switch (m_type)
    {
    case CToken::CType::plus:
        out << '+';
        break;
    case CToken::CType::minus:
        out << '-';
        break;
    case CToken::CType::multiplicate:
        out << '*';
        break;
    case CToken::CType::lparen:
        out << '(';
        break;
    case CToken::CType::rparen:
        out << ')';
        break;
    case CToken::CType::number:
        out << m_n.value();
        break;
    default:
        break;
    }
}

int CToken::priority() const
{
    switch (m_type)
    {
    case CType::plus:
        return 10;
    case CType::minus:
        return 10;
    case CType::multiplicate:
        return 20;
    case CType::divide:
        return 20;
    case CType::modulus:
        return 20;
    case CType::pow:
        return 30;
    default:
        return 0;
    }
}

CToken::CToken(const CToken &x)
    : m_type(x.m_type), m_n(x.m_n) {}

CToken &CToken::operator=(CToken x)
{
    swap(m_type, x.m_type);
    swap(m_n, x.m_n);
    return *this;
}

CNodePtr CToken::getNode(const CNodePtr &left, const CNodePtr &right) const
{
    switch (m_type)
    {
    case CType::plus:
        return CNodePtr(new CPlusNode(left, right));
    case CType::minus:
        return CNodePtr(new CMinusNode(left, right));
    case CType::multiplicate:
        return CNodePtr(new CMultNode(left, right));
    case CType::divide:
        return CNodePtr(new CDivideNode(left, right));
    case CType::modulus:
        return CNodePtr(new CModulusNode(left, right));
    case CType::pow:
        return CNodePtr(new CPowNode(left, right));
    default:
        throw logic_error("invalid token");
    }
}

CNodePtr CToken::getNode() const
{
    if (m_type != CType::number)
        throw logic_error("invalid token");
    return CNodePtr(new CNumNode(m_n.value()));
}