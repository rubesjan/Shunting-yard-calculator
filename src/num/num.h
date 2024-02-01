#ifndef NUM586259
#define NUM586259

#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

class CNum;
using CNumPtr = std::shared_ptr<CNum>;
using namespace std;

/**
 * @brief Abstract class representing number with unlimited precision.
 *
 * Numbers are expected to be stored in complement code with unlimited precision. H
 */
class CNum
{
public:
    /**
     * @brief Construct a new CNum object
     *
     */
    CNum();
    CNum(const CNum &x) = delete;
    /**
     * @brief Destroy the CNum object
     *
     */
    virtual ~CNum();
    /**
     * @brief returns x-th byte of number
     *
     * @param x - which byte is returned
     * @return uint8_t - the actual x-th byte of the number
     */
    virtual uint8_t getByte(const size_t &x) const = 0;
    /**
     * @brief Set the x-th byte of the number to val
     *
     * @param x - which byte is suppoes to be set
     * @param val - value of the byte
     */
    virtual void setByte(const size_t &x, const uint8_t val) = 0;
    /**
     * @brief returns size of the number - number of bytes
     *
     * @return size_t - size of the number in bytes
     */
    virtual size_t size() const = 0;
    /**
     * @brief Get the Exponent of the number, base of the exponent is 10
     *
     * @return int32_t - exponent
     */
    virtual int32_t getExponent() const = 0;
    /**
     * @brief If the number is decimal
     *
     * @return true - number is decimal
     * @return false - number is not decimal
     */
    virtual bool isDecimal() const = 0;
    /**
     * @brief if the number is negative
     *
     * @return true - number is negative
     * @return false - number is positive
     */
    virtual bool isNegative() const = 0;
    /**
     * @brief if the number is positive
     *
     * @return true - number is positive
     * @return false - number is negative
     */
    virtual bool isPositive() const = 0;
    /**
     * @brief Returns shared pointer to a new number which has decreased exponent.
     *
     * Decreases exponent of this number to the given number n. Value of the number is unchanged, but internal representation is changed
     *
     * @param n - to which exponent this number should be decreased
     * @return CNumPtr - new number with decreased exponent
     */
    virtual CNumPtr decExponent(const int32_t &n) = 0;
    /**
     * @brief Set the Exponent to given value.
     *
     * Value of this number is changed only by multiple of 10.
     *
     * @param e - value to which an exponent is set
     */
    virtual void setExponent(int32_t e) = 0;
    /**
     * @brief clones this number
     *
     * @return CNumPtr - new same number
     */
    virtual CNumPtr clone() const = 0;
    /**
     * @brief shifts this number byte-wise left by "s" bytes
     *
     * @param s - number of one byte shifts
     */
    virtual void LBShift(const uint32_t &s) = 0;
    /**
     * @brief shifts this number left by only one bit
     *
     */
    virtual void LBitShift();
    /**
     * @brief Get the bit-th bit of byte-th byte
     *
     * @param byte - which byte's bit is wanted
     * @param bit - which bit is wanted
     * @return uint8_t - value of the bit
     */
    virtual uint8_t getBit(const uint32_t &byte, const uint8_t &bit) const;
    /**
     * @brief get the number in a string
     *
     * @return string - number in the string
     */
    virtual string print() const;
};

/**
 * @brief Divides two CNums. Only integer division.
 *
 * If one of input numbers is decimal exception invalid_argument is thrown.
 * If divisor is 0, exception logic_error is thrown.
 *
 * @param a - dividend
 * @param b - divisor
 * @return pair<CNumPtr, CNumPtr> - first is result - integer, second is a remainder
 */
pair<CNumPtr, CNumPtr> divide(const CNumPtr &a, const CNumPtr &b);

CNumPtr operator+(CNumPtr a, CNumPtr b);
CNumPtr operator*(CNumPtr a, CNumPtr b);
CNumPtr operator-(CNumPtr a, CNumPtr b);
bool operator<(CNumPtr a, CNumPtr b);
bool operator==(CNumPtr a, CNumPtr b);
CNumPtr operator/(const CNumPtr &a, const CNumPtr &b);
CNumPtr operator%(const CNumPtr &a, const CNumPtr &b);

/**
 * @brief Power of a number
 *
 * If pow is decimal or negative number exception invalid_argument is thrown.
 *
 * @param a - base
 * @param b - power
 * @return - CNumPtr shared pointer to the result
 */
CNumPtr pow(const CNumPtr &a, const CNumPtr &b);
/**
 * @brief Power of a number, pow is a long long
 *
 * @param a  -base
 * @param pow - power
 * @return CNumPtr - shared pointer to the result
 */
CNumPtr pow(const CNumPtr &a, const unsigned long long &pow);

/**
 * @brief Cumputes factorial of a given number
 *
 * If input is decimal or negative number exception invalid_argument is thrown.
 *
 * @param a - the number
 * @return CNumPtr - shared pointer to the result
 */
CNumPtr factorial(const CNumPtr &a);

/**
 * @brief Round a number to integer
 *
 * @param n - number to round
 * @return CNumPtr - shared pointer to the result
 */
CNumPtr round(const CNumPtr &n);

/**
 * @brief Get CNum from vector of bytes of the number
 *
 * Based on density of digits - bytes of the number, decides to create CLong or CShort and returns shared pointer to abstract parent class CNum.
 * @param n - vector of bytes of the number
 * @param e - exponent of the number
 * @return CNumPtr - shared pointer to the number, can be CLong or CShort
 */
CNumPtr getCNumPtr(const vector<uint8_t> &n, const int32_t &e);
/**
 * @brief Get CNum from vector of bytes of the number
 *
 * Based on density of digits - bytes of the number, decides to create CLong or CShort and returns raw pointer to abstract parent class CNum.
 * @param n - vector of bytes of the number
 * @param e - exponent of the number
 * @return CNum*  - raw pointer to the number
 */
CNum *getCNumRaw(const vector<uint8_t> &n, const int32_t &e);
/**
 * @brief Multiplicates CNum by one byte
 *
 * @param n - raw pointer to the CNum number
 * @param b - byte to multiplicate with
 * @param k - number of left byte shifts of the result, default is 0
 * @return CNumPtr - shared pointer to the result
 */
CNumPtr multByte(CNum *n, const uint8_t b, size_t k = 0ul);
/**
 * @brief Negates the given CNum, using complementary code
 *
 * @param a - CNum to negate
 * @return CNumPtr - shared pointer to the result
 */
CNumPtr negateCNum(const CNum &a);
/**
 * @brief Get CNum from the given string
 *
 * @param str - string containing a number
 * @return CNumPtr - shared pointer to the number
 */
CNumPtr getCNum(const string &str);

ostream &operator<<(ostream &out, const CNumPtr &n);

#endif