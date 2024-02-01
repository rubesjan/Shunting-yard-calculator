#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <deque>

#include "num.h"
#include "long.h"

CLong::CLong(const vector<uint8_t> &n)
    : m_n{}, m_exponent(0), m_positive(true)
{
    if (n.empty())
        return;

    m_positive = !(n[n.size() - 1] & (1 << 7)); // highest bit of the number

    for (size_t i = 0; i < n.size(); i++) // for every byte of the number in given vector
    {
        this->setByte(i, n[i]);
    }
}

CLong::CLong(int16_t num)
    : m_n{}, m_exponent(0), m_positive(true)
{
    if (num >= 0)
        m_positive = true;
    else
        m_positive = false;

    for (size_t i = 0; i < 4; i++) // for every byte of num
    {
        m_n.emplace_back((num >> (8 * i)) & 0xff);
    }

    // delete 0s from the end
    for (int i = (m_n.size() - 1); i > 0; i--)
    {
        if ((num >= 0 && m_n[i] == 0) || (num < 0 && m_n[i] == 255))
            m_n.pop_back();
        else
            break;
    }
}

CLong::CLong(const CLong &x)
    : m_n(x.m_n), m_exponent(x.m_exponent), m_positive(x.m_positive) {}

CLong::~CLong() {}

uint8_t CLong::getByte(const size_t &x) const
{
    if (x >= m_n.size() && this->isPositive())
        return 0;
    else if (x >= m_n.size() && this->isNegative())
        return 255;

    return m_n[x];
}

void CLong::setByte(const size_t &x, const uint8_t val)
{
    if (x >= m_n.size())
    {
        for (size_t i = m_n.size(); i <= x; i++)
        {
            m_n.emplace_back(0);
        }
    }
    m_n[x] = val;
}

size_t CLong::size() const
{
    if (m_n.empty())
        return 0;
    return m_n.size() + 1;
}

bool CLong::isDecimal() const
{
    return m_exponent < 0;
}

bool CLong::isNegative() const
{
    return !m_positive;
}

bool CLong::isPositive() const
{
    return !(this->isNegative());
}

int32_t CLong::getExponent() const
{
    return m_exponent;
}

CNumPtr CLong::decExponent(const int32_t &n)
{
    CNumPtr tmpTH(nullptr);
    CNum *th = this;
    if (this->isNegative())
    {
        tmpTH = negateCNum(*this);
        th = tmpTH.get();
    }

    if (m_exponent <= n)
    {
        return CNumPtr(this->clone());
    }

    int32_t h = (m_exponent - n) / 2;

    CNumPtr tmp(nullptr);
    if ((m_exponent - n) % 2 == 0)
    {
        tmp = multByte(th, 100);
        h--;
    }
    else
    {
        tmp = multByte(th, 10);
    }

    // multiplication
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

CNumPtr CLong::clone() const
{
    return CNumPtr(new CLong(*this));
}

void CLong::setExponent(int32_t e)
{
    swap(m_exponent, e);
}

void CLong::LBShift(const uint32_t &s)
{
    if (s <= 0)
        return;

    if (this->isPositive())
        for (size_t i = 0; i < s; i++)
            m_n.insert(m_n.begin(), 0);
    else
        for (size_t i = 0; i < s; i++)
            m_n.insert(m_n.begin(), 255);
}