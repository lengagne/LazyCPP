#include "LazyValue.hpp"
#include "LazyOperator1.hpp"
#include "LazyOperator2.hpp"
#include "LazyAdditionX.hpp"
#include "LazyMultiplicationX.hpp"
bool compareLazyValue(const LazyValue* a, const LazyValue* b) 
{
    std::cout<<"compareLazyValue debut"<<std::endl;
    std::cout<<"Compare a = "<< *a <<" :" <<a->type_<<std::endl;
    std::cout<<"Compare b = "<< *b <<" :" <<b->type_<<std::endl;
    if (a->type_ != b->type_)
    {
        std::cout<<"Check by type : "<< (a->type_ < b->type_)<<std::endl;
        return a->type_ < b->type_;
    } else
    {
        switch (a->type_)
        {
            case(LAZYINPUT):    
                std::cout<<"Check LAZYINPUT : "<< ( a->id_ < b->id_) <<std::endl;
                return a->id_ < b->id_;
            case(LAZYCONSTANT):      
                std::cout<<"Check LAZYCONSTANT : "<< (a->value_ < b->value_)<<std::endl;
                return a->value_ < b->value_;
                
            case(LAZYCOSINUS):
            case(LAZYSINUS):
                std::cout<<"Check Operator1 "<< (((LazyOperator1 *) a)->a_ < ((LazyOperator1 *)b)->a_) <<std::endl;
                return ( ((LazyOperator1 *) a)->a_ < ((LazyOperator1 *)b)->a_);

            case(LAZYADDITION):
            case(LAZYMULTIPLICATION):
            case(LAZYSOUSTRACTION):
                std::cout<<"Check Operator2"<<std::endl;
                if ( compareLazyValue(((LazyOperator2 *)a)->a_,((LazyOperator2 *)b)->a_))
                {
                    std::cout<<"Check1 Operator2 true"<<std::endl;
                    return true;
                }
                if ( compareLazyValue(((LazyOperator2 *)b)->a_,((LazyOperator2 *)a)->a_))
                {
                    std::cout<<"Check2 Operator2 false"<<std::endl;
                    return false;        
                }
                if ( compareLazyValue(((LazyOperator2 *)a)->b_,((LazyOperator2 *)b)->b_))
//                 if (((LazyOperator2 *)a)->b_ < ((LazyOperator2 *)b)->b_)
                {
                    std::cout<<"Check3 Operator2 true"<<std::endl;
                    return true;
                }
                std::cout<<"Check4 Operator2 false"<<std::endl;
                return false;
            case(LAZYADDITIONX):
                std::cout<<"Check LazyAdditionX false"<<std::endl;
//                 if (((LazyAdditionX *)a)->coeff_:=  ((LazyAdditionX *)b)->coeff_))
//                     return ((LazyAdditionX *)a)->coeff_<  ((LazyAdditionX *)b)->coeff_)
                return (  (((LazyAdditionX *)a)->p_ < (((LazyAdditionX *)b)->p_)));
            case(LAZYMULTIPLICATIONX):
                std::cout<<"Check LazyMultiplicationX false"<<std::endl;
//                 if (((LazyMultiplicationX *)a)->coeff_:=  ((LazyMultiplicationX *)b)->coeff_))
//                     return ((LazyMultiplicationX *)a)->coeff_<  ((LazyMultiplicationX *)b)->coeff_);
                return (  (((LazyMultiplicationX *)a)->p_ < (((LazyMultiplicationX *)b)->p_)));
//                 if (((LazyOperatorX *)a)->p_.size() < ((LazyOperatorX *)b)->p_.size())
//                 {
// //                     std::cout<<"Check1 OperatorX true"<<std::endl;
//                     return true;
//                 }
//                 if (((LazyOperatorX *)a)->p_.size() > ((LazyOperatorX *)b)->p_.size()) 
//                 {
// //                     std::cout<<"Check2 OperatorX false"<<std::endl;
//                     return false;
//                 }
// /*                std::cout<<"Check3 OperatorX "<<  (((LazyOperatorX *)a)->p_ < ((LazyOperatorX *)b)->p_)<<std::endl;
//                 for(auto& i : ((LazyOperatorX *)a)->p_)
//                     std::cout<<"a : "<< *i <<std::endl;
//                 for(auto& i : ((LazyOperatorX *)b)->p_)
//                     std::cout<<"b : "<< *i <<std::endl;      */          
//                 return (((LazyOperatorX *)a)->p_ < ((LazyOperatorX *)b)->p_);
                
            case(LAZYUNDEFINED):
            default:
                std::cout<<"default"<<std::endl; 
                return a < b;
        }
    }
    std::cout<<"gloups "<<std::endl;
}

bool operator<(const std::list<LazyValue*>& lhs, const std::list<LazyValue*>& rhs) 
{
//     std::cout<<"operator < "<<std::endl;
    if (lhs.size() != rhs.size())
        return (lhs.size() < rhs.size());
    
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();

    while (it1 != lhs.end() && it2 != rhs.end()) {
        
        if ( *it1 != *it2)
        {
            
            if (compareLazyValue(*it1, *it2)) {
    //             std::cout<<"operator < TRUE"<<std::endl;
                return true; // lhs a un élément plus petit
            }
            if (compareLazyValue(*it2, *it1))
            {
    //             std::cout<<"operator < FALSE"<<std::endl;
                return false; // rhs a un élément plus petit
            }
        }
        ++it1;
        ++it2;
    }

    // Si tous les éléments sont égaux jusqu'ici, la plus courte liste est plus petite
//     std::cout<<"operator < "<< (lhs.size() < rhs.size()) <<std::endl;
    return (lhs.size() < rhs.size());
}

