#include <cstdlib>
#include "multnode.h"

CMultNode::CMultNode(const CNodePtr &left, const CNodePtr &right)
    : CBOperator(left, right) {}

CMultNode::~CMultNode() {}

number CMultNode::evaluate() const
{
    return (m_left->evaluate() * m_right->evaluate());
}