#include <cstdlib>
#include "modulusnode.h"

CModulusNode::CModulusNode(const CNodePtr &left, const CNodePtr &right)
    : CBOperator(left, right) {}

CModulusNode::~CModulusNode() {}

number CModulusNode::evaluate() const
{
    return (m_left->evaluate() % m_right->evaluate());
}