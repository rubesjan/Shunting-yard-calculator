#include <cstdlib>
#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <iterator>
#include <climits>

#include "num.h"
#include "short.h"

CShort::CShort(const vector<uint8_t> &n)
    : m_n{}, m_exponent(0), m_positive(true)
{
    if (n.empty())
        return;

    m_positive = !(n[n.size() - 1] & (1 << 7)); // highest bit of the number
    for (size_t i = 0; i < n.size(); i++)       // for every byte of the number in given vector
    {
        this->setByte(i, n[i]);
    }
}

CShort::CShort(int32_t num)
    : m_n{}, m_exponent(0), m_positive(false)
{
    if (num >= 0)
        m_positive = true;
    else
        m_positive = false;

    int size = 4;

    // count number of not null bytes
    for (int i = size - 1; i > 0; i--)
    {
        uint8_t b = ((num >> (8 * i)) & 0xff);
        if ((num >= 0 && b == 0) || (num < 0 && b == 255))
            size--;
    }

    // set not null bytes
    for (int i = 0; i < size; i++) // for every byte of uint32_t
    {
        m_n.emplace(make_pair(i, ((num >> (8 * i)) & 0xff)));
    }
}

CShort::CShort(const CShort &x)
    : m_n(x.m_n), m_exponent(x.m_exponent), m_positive(x.m_positive) {}

CShort::~CShort() {}

uint8_t CShort::getByte(const size_t &x) const
{
    auto tmp = m_n.find(x);
    if (tmp == m_n.end())
    {
        if (this->isNegative())
            return 255;
        return 0;
    }
    else
        return tmp->second;
}

void CShort::setByte(const size_t &x, const uint8_t val)
{
    if ((this->isPositive() && val == 0) || (this->isNegative() && val == 255)) // null value is not set
        return;

    auto tmp = m_n.emplace(x, val);
    if (!tmp.second)
        tmp.first->second = val;
}

size_t CShort::size() const
{
    if (m_n.empty())
        return 0;

    return m_n.rbegin()->first + 2;
}

bool CShort::isDecimal() const
{
    return m_exponent < 0;
}

bool CShort::isNegative() const
{
    return !m_positive;
    return (this->getByte(this->size() - 1) & (1 << 7));
}

bool CShort::isPositive() const
{
    return !(this->isNegative());
}

int32_t CShort::getExponent() const
{
    return m_exponent;
}

CNumPtr CShort::decExponent(const int32_t &n)
{
    if (m_exponent <= n)
    {
        return CNumPtr(this->clone());
    }

    CNumPtr tmpTH(nullptr);
    CNum *th = this;
    if (this->isNegative())
    {
        tmpTH = negateCNum(*this);
        th = tmpTH.get();
    }

    int32_t h = (m_exponent - n) / 2;

    CNumPtr tmp(nullptr);
    // do the first multiplication to get even number of future multiplications by 10
    if ((m_exponent - n) % 2 == 0)
    {
        tmp = multByte(th, 100);
        h--;
    }
    else
    {
        tmp = multByte(th, 10);
    }

    // multiplication by 100
    for (int32_t i = 0; i < h; i++)
    {
        tmp = multByte(tmp.get(), 100);
    }

    if (this->isNegative())
    {
        tmp = negateCNum(*tmp);
    }
    tmp->setExponent(n);
    return tmp;
}

CNumPtr CShort::clone() const
{
    return CNumPtr(new CShort(*this));
}

void CShort::setExponent(int32_t e)
{
    swap(m_exponent, e);
}

void CShort::LBShift(const uint32_t &s)
{
    if (s <= 0)
        return;

    auto it = m_n.begin();
    map<size_t, uint8_t> tmp;
    while (it != m_n.end())
    {
        tmp.emplace((it->first + s), it->second);
        ++it;
    }

    swap(m_n, tmp);
}