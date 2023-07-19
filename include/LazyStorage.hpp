#ifndef __LAZYSTORAGE_HPP__
#define __LAZYSTORAGE_HPP__

#include <map>
#include "LazyOperator2.hpp"

class LazyStorage
{
public:
    LazyStorage();
    
    ~LazyStorage();
    
    void clear();
    
    bool look_for (LazyOperator2* * item) const;
    
    void re_init_known();
    
    void store( LazyOperator2* item);
    
private:    
   
    std::map< LazyValue*, std::map<LazyValue*, LazyOperator2* > > storage_;
};

#endif // __LAZYMANAGER_HPP__
