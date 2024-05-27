#include "LazyValue.hpp"

bool compareLazyValue(LazyValue* a, LazyValue* b) 
{
//     std::cout<<"compareLazyValue"<<std::endl;
//     std::cout<<"a = " << *a <<std::endl;
//     std::cout<<"b = " << *b <<std::endl;
    if (a->type_ != b->type_)
    {
        return a->type_ < b->type_;
    }
    if ( a->id_ != b->id_)
        return a->id_ < b->id_;
    
    return a < b;
    
}
