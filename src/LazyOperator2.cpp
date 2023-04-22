#include "LazyOperator2.hpp"

void LazyOperator2::add_to_list(std::vector<LazyValue*>& vec)
{
    if (!known_)
    {
        a_->add_to_list(vec);
        b_->add_to_list(vec);
        vec.push_back(this);            
    }
    known_ =true;
}    
    

void LazyOperator2::check_known()
{
    if(!known_)
    {
        a_->check_known();
        b_->check_known();
    }
    known_ = true;
}
       
bool LazyOperator2::operator == (const LazyOperator2& A) const
{
    return (a_ == A.a_ && b_ == A.b_) || (a_ == A.b_ && b_ == A.a_);
}

