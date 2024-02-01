#ifndef SHORT593515
#define SHORT593515

#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "num.h"

using namespace std;

/**
 * @brief Represents number with high number of null bytes.
 *
 * Stored using complement code. Only bytes other than 0 for positive numbers (255 for negative numbers) are stored in a map. Highest bytes are not stored - 0 for positive number 255 for negative numbers. Key is power of the "digit", value is value of the digit - byte. Unlimited precision.
 *
 */
class CShort : public CNum
{
public:
    /**
     * @brief Construct a new CShort object from vector containing bytes of the number
     *
     * @param n vector containing bytes of the number, using complement code
     */
    CShort(const vector<uint8_t> &n);
    /**
     * @brief Construct a new CShort object from long long
     *
     * @param n value of the number
     */
    CShort(int32_t n);
    /**
     * @brief Construct a new CShort object
     *
     * @param x copy
     */
    CShort(const CShort &x);
    CShort &operator=(const CShort &x) = delete;
    /**
     * @brief Destroy the CShort object
     *
     */
    ~CShort();
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
     * @brief container containing bytes of the number.
     *
     * Key is power of the byte - digit. Value is value of the byte. Stored in complement code.
     *
     */
    map<size_t, uint8_t> m_n;
    /**
     * @brief exponent of the number
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