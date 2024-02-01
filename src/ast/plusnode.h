#ifndef PLUSNODE985236
#define PLUSNODE985236

#include <cstdlib>
#include "boperator.h"

/**
 * @brief Represents an addition node (plus operator) in AST
 *
 */
class CPlusNode : public CBOperator
{
public:
    /**
     * @brief Construct a new CPlusNode object with its operands
     *
     * @param left - left operand of the addition
     * @param right - right operand of the addition
     */
    CPlusNode(const CNodePtr &left, const CNodePtr &right);
    CPlusNode(const CPlusNode &x) = delete;
    CPlusNode &operator=(const CPlusNode &x) = delete;
    /**
     * @brief Destroy the CPlusNode object
     *
     */
    virtual ~CPlusNode();
    /**
     * @brief Get resolution of this addition CNode
     *
     * @return number
     */
    number evaluate() const override;
};

#endif