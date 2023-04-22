#include "LazyOperator1.hpp"

void LazyOperator1::add_to_list(std::vector<LazyValue*>& vec)
{
    if (!known_)
    {
        a_->add_to_list(vec);
        vec.push_back(this);            
    }
    known_ =true;
}   

void LazyOperator1::check_known()
{
    if(!known_)
        a_->check_known();
    known_ = true;
}
   
bool LazyOperator1::operator == (const LazyOperator1& A) const
{
    return (a_ == A.a_ );
}
    
