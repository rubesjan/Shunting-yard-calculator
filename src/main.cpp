#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "calc.h"
#include "num/long.h"
#include "num/num.h"
#include "num/short.h"

// #define TEST

int main()
{

#ifdef TEST

    CNumPtr k(new CLong(10));
    CNumPtr l(new CShort(20));
    assert(k < l);
    assert(l < (k * CNumPtr(new CLong(200))));

    CNumPtr p(new CShort(20));
    p->LBitShift();
    assert(p->print() == "40"s);
    p->LBShift(1);
    assert(p->print() == "10240"s);

    assert((l / k)->print() == "2"s);
    assert((k + l)->print() == "30"s);
    assert(negateCNum(*k)->print() == "-10"s);
    assert((k - l)->print() == "-10"s);
    assert(multByte(k.get(), 10)->print() == "100"s);
    assert((k * l)->print() == "200"s);
    assert(pow(l, 2)->print() == "400"s);
    assert(factorial(l)->print() == "2432902008176640000"s);
    assert(factorial(k)->print() == "3628800"s);
    assert((k % l)->print() == "10"s);
    assert((l % k)->print() == "0"s);

#endif
    CCalc c;
    c.run();

    return 0;
}