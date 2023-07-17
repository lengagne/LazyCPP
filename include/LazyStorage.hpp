#ifndef __LAZYSTORAGE_HPP__
#define __LAZYSTORAGE_HPP__

#include <map>
#include "LazyCPP.hpp"


class LazyStorage
{
public:
    LazyStorage()
    {
        storage_.clear();
    }
   
    bool look_for (LazyOperator2* * item) const
    {
        LazyOperator2* i = (LazyOperator2*) *item;
        std::map<LazyValue*, std::map<LazyValue*, LazyOperator2*> >::const_iterator ita = storage_.find(i->a_);
        if (ita == storage_.end())
        {
            return false;
        }
        const std::map<LazyValue*, LazyOperator2* >& M = ita->second;
        std::map<LazyValue*, LazyOperator2* >::const_iterator itb = M.find(i->b_);
        if (itb == M.end())
        {
            return false;
        }
        delete *item;
        *item = itb->second;
        return true;
        
    }
    
    void store( LazyOperator2* item)
    {
        storage_[item->a_][item->b_] = item;
    }
    
private:    
   
    std::map< LazyValue*, std::map<LazyValue*, LazyOperator2* > > storage_;
};



#endif // __LAZYMANAGER_HPP__
