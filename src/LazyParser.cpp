// #include "LazyParser.hpp"
#include "LazyCPP.hpp"

bool compareLazyParser(const LazyParser* a,
                        const LazyParser* b)
{
    if (a->typep_ != b->typep_)
    {
        // FIXME
        return (a->typep_ < b->typep_);
    }else
    {
        
        switch(a->typep_)
        {
            case(LAZYP_CONSTANT):
//                 std::cout<<"return "<<(*((LazyConstant*) a) < *((LazyConstant*) b))<<std::endl;
                return  (*((LazyConstant*) a) < *((LazyConstant*) b));
//             case(LAZYC_ADDITION):
// //                 std::cout<<"return "<<(*((LazyAddition*) a) < *((LazyAddition*) b))<<std::endl;
//                 return  (*((LazyAddition*) a) < *((LazyAddition*) b));
// 
//             case(LAZYC_MULTIPLICATION):
// //                 std::cout<<"return "<<(*((LazyMultiplication*) a) < *((LazyMultiplication*) b))<<std::endl;
//                 return  (*((LazyMultiplication*) a) < *((LazyMultiplication*) b));
                
            default:
//                 std::cout<<"compareLazyCreator type :" << a->typec_ <<"=="<< b->typec_<<" return by default "<<(a<b)<<std::endl;
                return (a < b);
        }        
        return (a<b);
    }
}

std::ostream& operator<< (std::ostream& stream, const LazyParser& v)
{
//     v.ref_->print_equation();
//     stream << v.ref_->value_;
    stream <<"[TYPE: "<< v.typep_ <<" : "<<   v.get_name()<< "]";
    return stream;
}
   
