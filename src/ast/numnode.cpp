#include <cstdlib>
#include <iostream>

#include "../num/num.h"
#include "numnode.h"

CNumNode::CNumNode(const number num)
    : m_n(num) {}

CNumNode::~CNumNode() {}

number CNumNode::evaluate() const
{
    return m_n;
}