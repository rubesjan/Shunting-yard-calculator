#ifndef NODE542595
#define NODE542595

#include <cstdlib>
#include <memory>

#include "../num/num.h"

class CNode;

using number = CNumPtr;
using CNodePtr = std::shared_ptr<CNode>;

/**
 * @brief Abstract class representing node in AST
 *
 */
class CNode
{
public:
    /**
     * @brief Construct a new CNode object
     *
     */
    CNode();
    CNode(const CNode &x) = delete;
    CNode &operator=(const CNode &x) = delete;
    /**
     * @brief Destroy the CNode object
     *
     */
    virtual ~CNode();
    /**
     * @brief Get result of this node
     *
     * @return number - result of this operation or value of number
     */
    virtual number evaluate() const = 0;
};

#endif