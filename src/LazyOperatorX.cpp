#include "LazyOperatorX.hpp"

void LazyOperatorX::add_to_list(std::vector<LazyValue*>& vec)
{
    if (!known_)
    {
        for (auto iter : p_)
            iter->add_to_list(vec);
        vec.push_back(this);            
    }
    known_ =true;
}    
    
void LazyOperatorX::check_known()
{
    if(!known_)
    {
        for (auto iter : p_)
            iter->check_known();
    }
    known_ = true;
}    
       
bool LazyOperatorX::operator == (const LazyOperatorX& A) const
{
    if (p_.size() != A.p_.size())
        return false;
    
    return p_ == A.p_;
}

