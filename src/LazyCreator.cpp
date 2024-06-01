#include "LazyCPP.hpp"

bool compareLazyCreator(LazyCreator* a,
                        LazyCreator* b)
{
    if (a->typec_ != b->typec_)
    {
        // FIXME
        return (a->typec_ < b->typec_);
    }
    else
    {
        switch(a->typec_)
        {
            case(LAZYC_CONSTANT):
                return  (*((LazyConstant*) a) < *((LazyConstant*) b));
            case(LAZYC_ADDITION):
                return  (*((LazyAddition*) a) < *((LazyAddition*) b));
            case(LAZYC_INPUT):
                return  (*((LazyInput*) a) < *((LazyInput*) b));

            case(LAZYC_MULTIPLICATION):
                return  (*((LazyMultiplication*) a) < *((LazyMultiplication*) b));
            case(LAZYC_SOUSTRACTION):
                return  (*((LazySoustraction*) a) < *((LazySoustraction*) b));
                
            default:
                std::cout<<"compareLazyCreator type :" << a->typec_ <<"=="<< b->typec_<<" return by default "<<(a<b)<<std::endl;
                return (a < b);
        }
    }
    return a <b;
}

std::ostream& operator<< (std::ostream& stream, LazyCreator& v)
{
     stream <<  v.get_equation();
     return stream;
}
