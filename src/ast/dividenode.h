#ifndef DIVIDE985215
#define DIVIDE985215

#include <cstdlib>
#include "boperator.h"

/**
 * @brief Represents division operation - '/' in expression
 *
 */
class CDivideNode : public CBOperator
{
public:
    /**
     * @brief Construct a new CDivideNode object
     *
     * @param left dividend
     * @param right divisor
     */
    CDivideNode(const CNodePtr &left, const CNodePtr &right);
    CDivideNode(const CDivideNode &x) = delete;
    CDivideNode &operator=(const CDivideNode &x) = delete;
    /**
     * @brief Destroy the CDivideNode object
     *
     */
    virtual ~CDivideNode();
    number evaluate() const override;
};

#endif