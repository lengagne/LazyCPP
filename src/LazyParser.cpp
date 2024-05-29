#include "LazyParser.hpp"

bool compareLazyParser(const LazyParser* a,
                        const LazyParser* b)
{
    if (a->typep_ != b->typep_)
    {
        // FIXME
        return (a>b);
    }else
    {
        return (a->typep_ < b->typep_);
    }
}
