#include "LazyCPP.hpp"

bool compareLazyCreator(LazyCreator* a,
                        LazyCreator* b)
{
//     std::cout<<"compare a "<< a <<"@"<< a->typec_ << " : "<< a->get_equation() <<std::endl; 
//     std::cout<<"compare b "<< b <<"@"<< b->typec_ << " : "<< b->get_equation() <<std::endl;
    if (a->typec_ != b->typec_)
    {
        // FIXME
//         std::cout<<"return "<<(a->typec_ < b->typec_)<<std::endl;
        return (a->typec_ < b->typec_);
    }
    else
    {
        switch(a->typec_)
        {
            case(LAZYC_CONSTANT):
//                 std::cout<<"return "<<(*((LazyConstant*) a) < *((LazyConstant*) b))<<std::endl;
                return  (*((LazyConstant*) a) < *((LazyConstant*) b));
            case(LAZYC_ADDITION):
//                 std::cout<<"return "<<(*((LazyAddition*) a) < *((LazyAddition*) b))<<std::endl;
                return  (*((LazyAddition*) a) < *((LazyAddition*) b));
            case(LAZYC_INPUT):
//                 std::cout<<"return "<<(*((LazyAddition*) a) < *((LazyAddition*) b))<<std::endl;
                return  (*((LazyInput*) a) < *((LazyInput*) b));

            case(LAZYC_MULTIPLICATION):
//                 std::cout<<"return "<<(*((LazyMultiplication*) a) < *((LazyMultiplication*) b))<<std::endl;
                return  (*((LazyMultiplication*) a) < *((LazyMultiplication*) b));
            case(LAZYC_SOUSTRACTION):
//                 std::cout<<"return "<<(*((LazyMultiplication*) a) < *((LazyMultiplication*) b))<<std::endl;
                return  (*((LazySoustraction*) a) < *((LazySoustraction*) b));
                
            default:
                std::cout<<"compareLazyCreator type :" << a->typec_ <<"=="<< b->typec_<<" return by default "<<(a<b)<<std::endl;
                return (a < b);
        }
    }
//     std::cout<<"return "<<(a<b)<<std::endl;
    return a <b;
}

std::ostream& operator<< (std::ostream& stream, LazyCreator& v)
{
     stream <<  v.get_equation();
     return stream;
}
