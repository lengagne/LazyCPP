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

void LazyOperator1::compact()
{
    if (!compacted_)
    {
        compacted_ = true;
        a_->compact();
    }
}

LazyValue* LazyOperator1::explose()
{
    if (!explosed_)
    {
        explosed_ = true;
        a_ = a_->explose();
    }
    return this;
}

void LazyOperator1::propag_update()
{
    update_ = a_->update_;
}
   
bool LazyOperator1::operator == (const LazyOperator1& A) const
{
    return (a_ == A.a_ );
}
    
