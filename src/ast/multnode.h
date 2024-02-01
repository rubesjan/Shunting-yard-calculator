#ifndef MULTNODE659836
#define MULTNODE659836

#include <cstdlib>
#include "boperator.h"

/**
 * @brief Represents a multiplication node in AST
 *
 */
class CMultNode : public CBOperator
{
public:
    /**
     * @brief Construct a new CMultNode object with its operands
     *
     * @param left - left operand of the multiplication
     * @param right - right operand of the multiplication
     */
    CMultNode(const CNodePtr &left, const CNodePtr &right);
    CMultNode(const CMultNode &x) = delete;
    CMultNode &operator=(const CMultNode &x) = delete;
    /**
     * @brief Destroy the CMultNode object
     *
     */
    ~CMultNode();
    /**
     * @brief Get result of this multiplication
     *
     * @return number - result of this CNode
     */
    number evaluate() const override;
};

#endif