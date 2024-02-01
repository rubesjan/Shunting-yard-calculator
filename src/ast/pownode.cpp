#include <cstdlib>
#include "pownode.h"

CPowNode::CPowNode(const CNodePtr &left, const CNodePtr &right)
    : CBOperator(left, right) {}

CPowNode::~CPowNode() {}

number CPowNode::evaluate() const
{
    return pow(m_left->evaluate(), m_right->evaluate());
}