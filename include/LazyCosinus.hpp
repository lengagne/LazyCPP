#ifndef __LAZYCOSINUS_HPP__
#define __LAZYCOSINUS_HPP__
#include <math.h>
#include "LazyOperator1.hpp"

class LazyCosinus : public LazyOperator1 {
public:
    LazyCosinus(LazyValue* a){
        a_ = a;
        value_ = cos(a_->value_);
    }
    
    inline void compute()
    {
//         std::cout<<"Cosinus Compute a("<<a_->value_ <<")"<<std::endl;
        value_ = cos(a_->value_);
    }
    
//     double evaluate(uint index) 
//     {
// //         if (index > index_)
// //         {
// //             index_ = index;
//             value_ = cos(a_->evaluate(index_));
//             return value_;
// //         }
// //         std::cout<<"Add Use previous computation"<<std::endl;
//         return value_;
//     }
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";
        
        std::cout<<tab<<"("<<this<<"): COSINUS ("<<value_<<")"<<std::endl;
        a_->print(tab+"\t",index);
    }
    
    
private:

};

#endif //  __LAZYCOSINUS_HPP__
