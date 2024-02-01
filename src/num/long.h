#ifndef LONG259542
#define LONG259542

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <deque>

#include "num.h"

using namespace std;

/**
 * @brief Represents a number with dense digits in terms of bytes
 *
 * All bytes of the number are stored regardless of their value. Stored using complement code. Highest bytes are not stored - 0 for positive number 255 for negative numbers.  Unlimited precision.
 *
 */
class CLong : public CNum
{
public:
    /**
     * @brief Construct a new CLong object from given vector cointaining bytes of the number
     *
     * @param n vector of bytes of the number
     */
    CLong(const vector<uint8_t> &n);
    /**
     * @brief Construct a new CLong object from long long
     *
     * @param n value of the number
     */
    CLong(int16_t n);
    /**
     * @brief Construct a new CLong object
     *
     * @param x copy
     */
    CLong(const CLong &x);
    CLong &operator=(const CLong &x) = delete;
    /**
     * @brief Destroy the CLong object
     *
     */
    ~CLong();
    virtual uint8_t getByte(const size_t &x) const override;
    virtual void setByte(const size_t &x, const uint8_t val) override;
    virtual size_t size() const override;
    virtual bool isDecimal() const override;
    virtual bool isNegative() const override;
    virtual bool isPositive() const override;
    virtual int32_t getExponent() const override;
    virtual CNumPtr decExponent(const int32_t &n) override;
    virtual void setExponent(int32_t e) override;
    virtual CNumPtr clone() const override;
    virtual void LBShift(const uint32_t &s) override;

protected:
    /**
     * @brief container for storing bytes of the number
     *
     */
    vector<uint8_t> m_n;
    /**
     * @brief value of the exponent, base is 10
     *
     */
    int32_t m_exponent;
    /**
     * @brief if the number is positive
     *
     */
    bool m_positive;
};

#endif