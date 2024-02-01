#ifndef MODULUSNODE956235
#define MODULUSNODE956235

#include <cstdlib>
#include "boperator.h"

/**
 * @brief Represents modulation node in AST
 *
 */
class CModulusNode : public CBOperator
{
public:
    /**
     * @brief Construct a new CModulusNode object with its operands
     *
     * @param left - left operand of the modulation
     * @param right - right operand of the modulation
     */
    CModulusNode(const CNodePtr &left, const CNodePtr &right);
    CModulusNode(const CModulusNode &x) = delete;
    CModulusNode &operator=(const CModulusNode &x) = delete;
    /**
     * @brief Destroy the CModulusNode object
     *
     */
    virtual ~CModulusNode();
    /**
     * @brief Get result of modulation
     *
     * @return number - result of this CNode
     */
    number evaluate() const override;
};

#endif