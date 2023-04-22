#include "LazyOperator2.hpp"

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
