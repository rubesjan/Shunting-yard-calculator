#ifndef MINUSOPERATOR695841
#define MINUSOPERATOR695841

#include <cstdlib>
#include "boperator.h"

/**
 * @brief Represents a substraction (minus operator) node in AST
 *
 */
class CMinusNode : public CBOperator
{
public:
    /**
     * @brief Construct a new CMinusNode object with its operands
     *
     * @param left - left operand of the substraction
     * @param right - right operand of the substraction
     */
    CMinusNode(const CNodePtr &left, const CNodePtr &right);
    CMinusNode(const CMinusNode &x) = delete;
    CMinusNode &operator=(const CMinusNode &x) = delete;
    /**
     * @brief Destroy the CMinusNode object
     *
     */
    ~CMinusNode();
    /**
     * @brief Get resolution of this substraction.
     *
     * @return number resolution of this CNode
     */
    number evaluate() const override;
};

#endif