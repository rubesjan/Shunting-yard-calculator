#ifndef POWNODE851547
#define POWNODE851547

#include <cstdlib>
#include "boperator.h"

/**
 * @brief Represents power operator in AST
 *
 */
class CPowNode : public CBOperator
{
public:
    /**
     * @brief Construct a new CPowNode object with its operands
     *
     * @param left - left operand of the operation
     * @param right - right operand of the operation
     */
    CPowNode(const CNodePtr &left, const CNodePtr &right);
    CPowNode(const CPowNode &x) = delete;
    CPowNode &operator=(const CPowNode &x) = delete;
    /**
     * @brief Destroy the CPowNode object
     *
     */
    virtual ~CPowNode();
    /**
     * @brief Get result of the operation
     *
     * @return number - result of the operation
     */
    number evaluate() const override;
};

#endif