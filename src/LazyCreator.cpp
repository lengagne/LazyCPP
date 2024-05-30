#include "LazyCreator.hpp"
#include "LazyConstant.hpp"

bool compareLazyCreator(const LazyCreator* a,
                        const LazyCreator* b)
{
    if (a->typec_ != b->typec_)
    {
        // FIXME
        return (a->typec_ < b->typec_);
    }else
    {
        switch(a->typec_)
        {
            case(LAZYC_CONSTANT):
                return  (*((LazyConstant*) a) < *((LazyConstant*) b));
            default:
                return (a < b);
        }
    }
}

std::ostream& operator<< (std::ostream& stream, LazyCreator& v)
{
     stream <<  v.get_equation();
     return stream;
}
