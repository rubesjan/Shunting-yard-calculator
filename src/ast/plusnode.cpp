#include <cstdlib>
#include "plusnode.h"

CPlusNode::CPlusNode(const CNodePtr &left, const CNodePtr &right)
    : CBOperator(left, right) {}

CPlusNode::~CPlusNode() {}

number CPlusNode::evaluate() const
{
    return (m_left->evaluate() + m_right->evaluate());
}