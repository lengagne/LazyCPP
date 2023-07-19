#include "LazyStorage.hpp"

LazyStorage::LazyStorage()
{
    storage_.clear();
}

LazyStorage::~LazyStorage()
{
    clear();
}
    
void LazyStorage::clear()
{
    storage_.clear();
}   
   
bool LazyStorage::look_for (LazyOperator2* * item) const
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
    
void LazyStorage::re_init_known()
{
    for (auto& iter : storage_)
    {
        for (auto& lazy : iter.second)
            lazy.first->re_init_known();
    }
}
    
void LazyStorage::store( LazyOperator2* item)
{
    storage_[item->a_][item->b_] = item;
}

