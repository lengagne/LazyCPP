#include "LazyCreator.hpp"

bool compareLazyCreator(const LazyCreator* a,
                        const LazyCreator* b)
{
    if (a->typec_ != b->typec_)
    {
        // FIXME
        return (a>b);
    }else
    {
        return (a->typec_ < b->typec_);
    }
}
