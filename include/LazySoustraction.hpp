#ifndef __LAZYSOUSTRACTION_HPP__
#define __LAZYSOUSTRACTION_HPP__

#include "LazyOperator2.hpp"

class LazySoustraction : public LazyOperator2 {
public:
    LazySoustraction(LazyValue* a, LazyValue* b) {
        a_ =a;
        b_ = b;
        value_ = a->value_-b->value_;        
    }
    
    inline void compute()
    {
//         std::cout<<"Soustraction Compute a("<<a_->value_<<")-b("<<b_->value_<<")" <<std::endl;
        value_ = a_->value_ - b_->value_;
    }    
    
//     double evaluate(uint index) 
//     {
// //         if (index > index_)
// //         {
// //             index_ = index;
//             value_ = a_->evaluate(index_) - b_->evaluate(index_);
//             return value_;
// //         }
// //         std::cout<<"Sous Use previous computation"<<std::endl;
//         return value_;
//     }
    
    virtual void print( const std::string& tab ="",uint index=0) 
    {
//         if (index > index_)
//             std::cout<<"\x1B[35m";
//         else
//             std::cout<<"\x1B[32m";
        
        std::cout<<tab<<"("<<this<<") Soustraction ("<<value_<<")"<<std::endl;
        a_->print(tab+"\t",index);
        b_->print(tab+"\t",index);
    }
    
    virtual void print_equation()
    {
        std::cout<<"(";
        a_->print_equation();
        std::cout<<" - ";
        b_->print_equation();
        std::cout<<")";
    }
    
    virtual bool operator == (const LazyOperator2& A) const
    {
        return (a_ == A.a_ && b_ == A.b_);
    }    
    
private:
};


#endif // __LAZYSOUSTRACTION_HPP__
