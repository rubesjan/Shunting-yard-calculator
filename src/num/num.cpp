#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <climits>

#include "num.h"
#include "short.h"
#include "long.h"

CNum::CNum() {}

CNum::~CNum() {}

inline void CNum::LBitShift()
{
    if (this->size() == 0)
        return;

    uint8_t carry(0);
    if (this->isNegative())
        carry = 1;

    size_t size(this->size());
    for (size_t i = 0; i < (size + 1); i++)
    {
        uint8_t tmp(this->getByte(i));

        // carry from this byte:
        uint8_t tmpcarry((tmp >> 7) & 0x01);

        // left bit shift
        tmp = tmp << 1;

        // add carry from lower byte
        tmp &= 0xfe;
        tmp |= carry;

        // carry for next byte
        carry = tmpcarry;
        this->setByte(i, tmp);
    }
}

inline uint8_t CNum::getBit(const uint32_t &byte, const uint8_t &bit) const
{
    return (this->getByte(byte) >> bit) & 0x01;
}

string CNum::print() const
{
    // cout << "printing" << endl;
    CNumPtr th(this->isNegative() ? move(negateCNum(*this)) : this->clone());

    th = th->decExponent(min(0, th->getExponent()));

    int32_t digits(2.5 * (th->size()) + 1 + abs(th->getExponent())); // size * log10(256) + exponent

    CNumPtr pow(new CLong(10));

    string tmp;
    tmp.reserve(digits + 1); // plus one for '.'

    int32_t exponent(th->getExponent());
    CNumPtr num(th->clone());

    if (exponent < 0)
    {
        num->setExponent(0);
    }

    // the digits in reversed order
    for (int i = 0; i < digits; i++)
    {
        if (i == (-1 * exponent) && exponent != 0)
            tmp.push_back('.');

        auto x = divide(num, pow);
        num = x.first;
        tmp.push_back(x.second->getByte(0) + '0');
    }

    // erase all '0' from the end of the string
    auto it = tmp.rbegin();
    while (it != tmp.rend() && *it == '0')
    {
        tmp.pop_back();
        it = tmp.rbegin();
    }

    // add zero if this is decimal and |this| < 1 or this == 0
    if ((this->isDecimal() && th < CNumPtr(new CLong(1))) || th == CNumPtr(new CLong(0)))
    {
        tmp.push_back('0');
    }

    if (this->isNegative())
        tmp.push_back('-');

    reverse(tmp.begin(), tmp.end());
    return tmp;
}

inline CNumPtr getCNumPtr(const vector<uint8_t> &n, const int32_t &e)
{
    return CNumPtr(getCNumRaw(n, e));
}

inline CNum *getCNumRaw(const vector<uint8_t> &n, const int32_t &e)
{
    size_t zeros(0);
    if (n[n.size() - 1] & (1 << 7))
    {
        zeros = count(n.begin(), n.end(), (uint8_t)255);
    }
    else
    {
        zeros = count(n.begin(), n.end(), (uint8_t)0); // number of 0 bytes in the number
    }

    // decide what is more efficient
    if (zeros > (n.size() * 0.8)) // CShort
    {
        CNum *ptr(new CShort(n));
        ptr->setExponent(e);
        return ptr;
    }
    else // CLong
    {
        CNum *ptr(new CLong(n));
        ptr->setExponent(e);
        return ptr;
    }
}

inline CNumPtr operator+(CNumPtr a, CNumPtr b)
{
    int32_t sa = a->getExponent();
    int32_t sb = b->getExponent();
    int32_t exponent = min(sa, sb);

    // set same exponents
    if (sa < sb)
    {
        b = b->decExponent(sa);
    }
    else if (sb < sa)
    {
        a = a->decExponent(sb);
    }

    vector<uint8_t> tmp;
    uint8_t carry(0);
    size_t size = max(a->size(), b->size());

    // count the addition
    for (size_t i = 0; i < size + 2; i++)
    {
        uint16_t sum = a->getByte(i) + b->getByte(i) + carry;
        carry = (sum >> 8) & 0x01;
        tmp.emplace_back(sum);
    }

    // determine if long or short
    return getCNumPtr(tmp, exponent);
}

inline CNumPtr multByte(CNum *n, const uint8_t b, size_t k)
{
    CNumPtr tmpN;
    if (n->isNegative())
    {
        tmpN = negateCNum(*n);
        n = tmpN.get();
    }

    // for efficiency
    if (b == 0)
        return CNumPtr(new CLong(0));

    uint8_t carry(0);
    vector<uint8_t> tmp; // result
    tmp.reserve(n->size());

    for (size_t i = 0; i < k; i++) // left byte shift
        tmp.emplace_back(0);

    // the multiplication
    for (size_t i = 0; i < n->size() + 2; i++)
    {
        uint16_t res = (n->getByte(i) * b) + carry;
        carry = (res >> 8) & 0xff;
        tmp.emplace_back((res & 0xff));
    }
    if (carry)
        tmp.emplace_back(carry);

    auto res = getCNumPtr(tmp, n->getExponent());
    if (n->isNegative())
        res = negateCNum(*res);

    return res;
}

inline CNumPtr negateCNum(CNumPtr a)
{
    return negateCNum(*a);
}

inline CNumPtr negateCNum(const CNum &a)
{
    vector<uint8_t>
        tmp;

    // the negation
    for (size_t i = 0; i < (a.size() + 1); i++)
    {
        tmp.emplace_back(~(a.getByte(i)));
    }

    for (size_t i = 0; i < (a.size() + 1); i++)
    {
        tmp[i]++;
        if (tmp[i] != 0)
            break;
    }
    return getCNumPtr(tmp, a.getExponent());
}

inline CNumPtr operator*(CNumPtr a, CNumPtr b)
{
    size_t sb = b->size();

    int32_t exponent = a->getExponent() + b->getExponent();

    bool positive(true);
    if ((a->isPositive() && b->isNegative()) || (a->isNegative() && b->isPositive()))
        positive = false;

    sb++;
    if (a->isNegative())
    {
        a = negateCNum(a);
    }

    if (b->isNegative())
    {
        b = negateCNum(b);
    }

    CNumPtr sum(new CLong(0));
    // the multiplication
    for (size_t i = 0; i < sb; i++)
    {
        CNumPtr tmp(multByte(a.get(), b->getByte(i), i));
        sum = sum + tmp;
    }

    if (!positive)
        sum = negateCNum(*sum);

    sum->setExponent(exponent);
    return sum;
}

CNumPtr operator-(CNumPtr a, CNumPtr b)
{
    return (a + negateCNum(b));
}

CNumPtr pow(const CNumPtr &a, const unsigned long long &pow)
{
    CNumPtr res(new CLong(1));
    for (unsigned long long i = 0; i < pow; ++i)
    {
        res = res * a;
    }
    return res;
}

CNumPtr pow(const CNumPtr &a, const CNumPtr &b)
{
    if (b->isDecimal())
        throw std::invalid_argument("invalid exponent: exponent is decimal");

    if (b->isNegative())
        throw std::invalid_argument("invalid exponent: exponent is negative");

    unsigned long long p(0);
    if (b < CNumPtr(new CShort(INT32_MAX)))
    {
        p = atoll(b->print().data());
        return pow(a, p);
    }

    CNumPtr res(new CLong(1));

    for (CNumPtr i(new CLong(0)); i < b; i = i + CNumPtr(new CLong(1)))
    {
        res = res * a;
    }
    return res;
}

CNumPtr factorial(const CNumPtr &a)
{
    if (a->isDecimal())
        throw std::invalid_argument("invalid expression: factorial of decimal number");

    if (a->isNegative())
        throw std::invalid_argument("invalid expression: factorial of negative number");

    CNumPtr res(new CLong(1));
    for (CNumPtr tmp(a->clone()); CNumPtr(new CLong(0)) < tmp; tmp = tmp + CNumPtr(new CLong(-1)))
    {
        res = res * tmp;
    }
    return res;
}

CNumPtr round(const CNumPtr &n)
{
    if (!n->isDecimal())
        return n;
    if ((n->isPositive() && n < CNumPtr(new CLong(1))) || (n->isNegative() && CNumPtr(new CLong(-1)) < n))
        return CNumPtr(new CLong(0));

    string tmp(n->print());
    size_t dec(tmp.find('.'));

    // round it from the printed number
    CNumPtr res = getCNum(tmp.substr(0, dec));
    if (tmp[dec + 1] == '5')
    {
        if (n->isPositive())
            return res + CNumPtr(new CLong(1));
        return res + CNumPtr(new CLong(-1));
    }
    return res;
}

CNumPtr getCNum(const string &str)
{
    if (str.empty())
        return CNumPtr(new CLong(0));

    bool decimal = (str.find('.') != string::npos);
    CNumPtr pow(new CLong(1));
    CNumPtr num(new CLong(0));
    auto it = str.rbegin();
    while (it != str.rend() && isspace(*it)) // skip WS in the beginning
        ++it;

    if (decimal)
    {
        size_t decsize = (str.size() - 1 - str.find('.'));
        pow->setExponent(-1 * decsize);
        while (*it != '.') // get the decimal part of the number
        {
            num = num + multByte(pow.get(), (*it) - '0');
            ++it;
            pow = multByte(pow.get(), 10);
        }
        ++it;
    };

    pow = CNumPtr(new CLong(1));
    while (it != str.rend() && isdigit(*it)) // integer part of the number
    {
        if (*it == '0')
        {
            pow = multByte(pow.get(), 10);
            ++it;
            continue;
        }
        num = num + multByte(pow.get(), (*it) - '0');
        pow = multByte(pow.get(), 10);
        ++it;
    }

    if (it != str.rend() && *it == '-') // if the number is negative
        num = negateCNum(*num);

    return num;
}

pair<CNumPtr, CNumPtr> divide(const CNumPtr &nn, const CNumPtr &dd)
{
    if (nn->isDecimal() || dd->isDecimal())
        throw invalid_argument("invalid division: decimal operand");

    if (dd == CNumPtr(new CLong(0)))
        throw logic_error("invalid division: division by zero");

    bool positive(true); // positivness of the result
    CNumPtr d;
    CNumPtr n;
    CNumPtr nd;
    // get absolute value of the numbers
    if (dd->isNegative())
    {
        nd = dd->clone();
        positive = !positive;
        d = negateCNum(*dd);
    }
    else
    {
        nd = negateCNum(*(dd.get()));
        d = dd->clone();
    }

    if (nn->isNegative())
    {
        positive = !positive;
        n = negateCNum(*nn);
    }
    else
        n = nn;

    CNumPtr q(new CLong(0));
    CNumPtr r(new CLong(0));
    // the division
    for (int i = (n->size()) * 8; i >= 0; i--)
    {
        r->LBitShift();
        uint8_t tmp(r->getByte(0) & 0xfe);
        r->setByte(0, tmp | n->getBit(i / 8, i % 8));
        if (d < r || d == r)
        {
            r = r + nd;
            uint8_t tmpq(q->getByte(i / 8));
            tmpq |= 1 << (i % 8);
            q->setByte(i / 8, tmpq);
        }
    }
    if (!positive)
    {
        q = negateCNum(*(q.get()));
        r = negateCNum(*(r.get()));
    }
    return make_pair(q, r);
}

inline bool operator<(CNumPtr a, CNumPtr b)
{
    if (a->isPositive() && b->isNegative())
        return false;
    else if (a->isNegative() && b->isPositive())
        return true;

    if (a->isNegative())
    {
        a = negateCNum(a);
        b = negateCNum(b);
        swap(a, b);
    }
    // set exponents to equal value
    size_t exponent = min(a->getExponent(), b->getExponent());
    if (a->getExponent() < b->getExponent())
        b = b->decExponent(exponent);
    else if (b->getExponent() < a->getExponent())
        a = a->decExponent(exponent);

    size_t size = max(a->size(), b->size());
    // the comparison
    for (int i = size - 1; i >= 0; --i)
    {
        uint8_t ba = a->getByte(i);
        uint8_t bb = b->getByte(i);
        if (ba != bb)
            return ba < bb;
    }
    // numbers are equal
    return false;
}

inline bool operator==(CNumPtr a, CNumPtr b)
{
    // set exponents to the same value
    if (a->getExponent() != b->getExponent())
    {
        if (a->getExponent() < b->getExponent())
            b = b->decExponent(a->getExponent());
        else if (b->getExponent() < a->getExponent())
            a = a->decExponent(b->getExponent());
    }
    // the comparison
    for (size_t i = 0; i < max(a->size(), b->size()); i++)
    {
        if (a->getByte(i) != b->getByte(i))
            return false;
    }
    return true;
}

CNumPtr operator/(const CNumPtr &a, const CNumPtr &b)
{
    return divide(a, b).first;
}

CNumPtr operator%(const CNumPtr &a, const CNumPtr &b)
{
    return divide(a, b).second;
}

ostream &operator<<(ostream &out, const CNumPtr &n)
{
    return out << n->print();
}