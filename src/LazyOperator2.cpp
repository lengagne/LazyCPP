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

void LazyOperator2::compact()
{
    if (!compacted_)
    {
        compacted_ = true;    
        a_->compact();
        b_->compact();
    }
}

LazyValue* LazyOperator2::explose()
{
    if (!explosed_)
    {
        explosed_ = true;
        a_ = a_->explose();
        b_ = b_->explose();
    }
    return this;
}

void LazyOperator2::propag_update()
{
    update_ = a_->update_ || b_->update_;
}
       
bool LazyOperator2::operator == (const LazyOperator2& A) const
{
    return (a_ == A.a_ && b_ == A.b_) || (a_ == A.b_ && b_ == A.a_);
}

