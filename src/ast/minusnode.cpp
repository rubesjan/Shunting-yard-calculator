#include <cstdlib>
#include "minusnode.h"

CMinusNode::CMinusNode(const CNodePtr &left, const CNodePtr &right)
    : CBOperator(left, right) {}

CMinusNode::~CMinusNode() {}

number CMinusNode::evaluate() const
{
    return (m_left->evaluate() - m_right->evaluate());
}