#include <cstdlib>
#include "dividenode.h"

CDivideNode::CDivideNode(const CNodePtr &left, const CNodePtr &right)
    : CBOperator(left, right) {}

CDivideNode::~CDivideNode() {}

number CDivideNode::evaluate() const
{
    return m_left->evaluate() / m_right->evaluate();
}