#include <cstdlib>
#include "boperator.h"

CBOperator::CBOperator(const CNodePtr &left, const CNodePtr &right)
    : m_left(left), m_right(right) {}

CBOperator::~CBOperator() {}