#ifndef __LAZYPARSER_HPP__
#define __LAZYPARSER_HPP__
#include <iostream>
#include "LazyCreator.hpp"

typedef enum LazyParserType{
    LAZYP_CONSTANT,         //0
    LAZYP_INPUT,            //1
    LAZYP_ADDITIONX,        //2
    LAZYP_MULTIPLICATIONX,  //3
    LAZYP_COSINUS,          //4
    LAZYP_SINUS,            //5
} LazyParserType;


class LazyCreator;

class LazyParser 
{
public:

    virtual LazyCreator* explose() = 0;
    
    virtual std::string get_name() const = 0;
    
    virtual bool is_zero() const =0;
    
    virtual void print( const std::string& tab="") const = 0; 

    LazyParserType typep_ = LAZYP_CONSTANT;

    friend std::ostream& operator<< (std::ostream& stream, const LazyParser& v);
    
protected:
    
    LazyCreator* explosed_ = nullptr;
    
private:

};

bool compareLazyParser(const LazyParser* a,const LazyParser* b);

#endif //  __LAZYPARSER_HPP__
