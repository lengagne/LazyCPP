#ifndef __LAZYOPERATORX_HPP__
#define __LAZYOPERATORX_HPP__

#include "LazyValue.hpp"

class LazyOperatorX : public LazyValue {
public:
    
    virtual void add_to_list(std::vector<LazyValue*>& vec)
    {
        if (!known_)
        {
            for (int i=0;i<p_.size();i++)
                p_[i]->add_to_list(vec);
            vec.push_back(this);            
        }
        known_ =true;
    }    
    
    virtual void check_known()
    {
        if(!known_)
        {
            for (int i=0;i<p_.size();i++)
                p_[i]->check_known();
        }
        known_ = true;
    }    
       
    virtual bool operator == (const LazyOperatorX& A) const
    {
        if (p_.size() != A.p_.size())
            return false;
        
        for (int i=0;i<p_.size();i++)
            if (p_[i] != A.p_[i])
                return false;
        
        return true;
    }
    
    std::vector<LazyValue*> p_;
};

#endif //  __LAZYADDITION_HPP__
