#ifndef BOPERATOR658547
#define BOPERATOR658547

#include <cstdlib>
#include "node.h"

/**
 * @brief Represents node in AST - binary operator in mathematical expression
 *
 */
class CBOperator : public CNode
{
public:
    /**
     * @brief Construct a new CBOperator object
     *
     * @param left operand of the operator
     * @param right operand of the operator
     */
    CBOperator(const CNodePtr &left, const CNodePtr &right);
    CBOperator(const CBOperator &x) = delete;
    CBOperator &operator=(const CBOperator &x) = delete;
    /**
     * @brief Evaluates the the operation
     *
     * @return number result of the operation
     */
    virtual number evaluate() const = 0;
    /**
     * @brief Destroy the CBOperator object
     *
     */
    virtual ~CBOperator();

protected:
    /**
     * @brief Operads of the operation
     *
     */
    CNodePtr m_left, m_right;
};

#endif