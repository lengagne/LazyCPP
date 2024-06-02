#include "LazyCPP.hpp"

LazyParser* LazyParser::simplify()
{
//     std::cout<<"debut ("<<this<<") simplify : "<< *this <<std::endl;
    if (simplified_ == nullptr)
    {
        simplified_ = do_simplification();
    }
//     std::cout<<"fin   ("<<this<<") simplify @"<<simplified_<<"@ : "<< *simplified_ <<std::endl;
    return simplified_;    
}

bool compareLazyParser(const LazyParser* a,
                        const LazyParser* b)
{
//     std::cout<<"Compare @"<<a<<"@ "<< *a <<"  @"<<b<<"@ "<< *b <<std::endl;
    if (a->typep_ != b->typep_)
    {
//         std::cout<<"CASE 1"<<std::endl;
        return (a->typep_ < b->typep_);
    }else
    {
        
        switch(a->typep_)
        {
            case(LAZYP_CONSTANT):
//                 std::cout<<"CASE 2"<<std::endl;
                return  (*((LazyConstant*) a) < *((LazyConstant*) b));
                
            case(LAZYP_INPUT):
//                 std::cout<<"CASE 3"<<std::endl;
                return  (*((LazyInput*) a) < *((LazyInput*) b));
                
            case(LAZYP_ADDITIONX):
//                 std::cout<<"CASE 4"<<std::endl;
                return  (*((LazyAdditionX*) a) < *((LazyAdditionX*) b));
// 
            case(LAZYP_MULTIPLICATIONX):
//                 std::cout<<"CASE 5"<<std::endl;
                return  (*((LazyMultiplicationX*) a) < *((LazyMultiplicationX*) b));

            case(LAZYP_COSINUS):
//                 std::cout<<"CASE 6"<<std::endl;
                return  (*((LazyCosinus*) a) < *((LazyCosinus*) b));

            case(LAZYP_SINUS):
//                 std::cout<<"CASE 7"<<std::endl;
                return  (*((LazySinus*) a) < *((LazySinus*) b));
                
            default:
//                 std::cout<<"compareLazyParser type :" << a->typep_ <<"=="<< b->typep_<<" return by default "<<(a<b)<<std::endl;
                return (a < b);
        }        
//         std::cout<<"CASE 8"<<std::endl;
        return (a<b);
    }
//     std::cout<<"CASE 9"<<std::endl;
}

std::ostream& operator<< (std::ostream& stream, const LazyParser& v)
{
    stream <<"[TYPE: "<< v.typep_ <<" : "<<   v.get_name()<< "]";
    return stream;
}
   
