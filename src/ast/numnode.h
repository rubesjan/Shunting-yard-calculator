#ifndef NUMNODE652415
#define NUMNODE652415

#include <cstdlib>
#include "node.h"

/**
 * @brief Represents number in AST
 *
 */
class CNumNode : public CNode
{
public:
    /**
     * @brief Construct a new CNumNode object with value
     *
     * @param num - value of the number
     */
    CNumNode(const number num);
    CNumNode(const CNumNode &x) = delete;
    CNumNode &operator=(const CNumNode &x) = delete;
    /**
     * @brief Destroy the CNumNode object
     *
     */
    virtual ~CNumNode();
    /**
     * @brief Get value of the number
     *
     * @return number - alias to shared pointer to the number
     */
    number evaluate() const;

protected:
    /**
     * @brief value of the number
     *
     */
    number m_n;
};

#endif