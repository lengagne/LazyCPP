#ifndef __LAZYPARSER_HPP__
#define __LAZYPARSER_HPP__
#include <iostream>
#include "LazyCreator.hpp"

typedef enum LazyParserType{
    LAZYP_UNDEFINED,
    LAZYP_INPUT,
    LAZYP_ADDITIONX,
    LAZYP_MULTIPLICATIONX,
    LAZYP_COSINUS,    
    LAZYP_SINUS,
} LazyParserType;


class LazyCreator;

class LazyParser 
{
public:

    virtual LazyCreator* explose() = 0;
    
    virtual bool is_zero() const =0;
    
    virtual void print( const std::string& tab="") const = 0; 

    LazyParserType typep_ = LAZYP_UNDEFINED;

protected:
    
    LazyCreator* explosed_ = nullptr;
    
private:

};

bool compareLazyParser(const LazyParser* a,const LazyParser* b);

#endif //  __LAZYPARSER_HPP__
