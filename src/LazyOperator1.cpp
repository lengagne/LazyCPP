#include "LazyOperator1.hpp"

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
    
