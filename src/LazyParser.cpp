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
                
            case(LAZYP_INPUT):
//                 std::cout<<"return "<<(*((LazyConstant*) a) < *((LazyConstant*) b))<<std::endl;
                return  (*((LazyInput*) a) < *((LazyInput*) b));
                
            case(LAZYP_ADDITIONX):
// //                 std::cout<<"return "<<(*((LazyAddition*) a) < *((LazyAddition*) b))<<std::endl;
                return  (*((LazyAdditionX*) a) < *((LazyAdditionX*) b));
// 
            case(LAZYP_MULTIPLICATIONX):
                return  (*((LazyMultiplicationX*) a) < *((LazyMultiplicationX*) b));

            case(LAZYP_COSINUS):
                return  (*((LazyCosinus*) a) < *((LazyCosinus*) b));

            case(LAZYP_SINUS):
                return  (*((LazySinus*) a) < *((LazySinus*) b));
                
            default:
                std::cout<<"compareLazyParser type :" << a->typep_ <<"=="<< b->typep_<<" return by default "<<(a<b)<<std::endl;
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
   
