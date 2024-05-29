#include "LazyCreator.hpp"

bool compareLazyCreator(const LazyCreator* a,
                        const LazyCreator* b)
{
    if (a->type_ != b->type_)
    {
        // FIXME
        return (a>b);
    }else
    {
        return (a->type_ < b->type_);
    }
}
