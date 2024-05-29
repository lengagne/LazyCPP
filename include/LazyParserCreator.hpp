#ifndef __LAZYPARSERCREATOR_HPP__
#define __LAZYPARSERCREATOR_HPP__

#include "LazyCreator.hpp"
#include "LazyParser.hpp"

class LazyParserCreator : public LazyParser, public LazyCreator
{
public:
    
    
    virtual LazyCreator* explose()
    {
        return this;
    }
    
    virtual bool is_zero() const
    {
        return false;
    }
protected:    
    
private:

};


#endif //  __LAZYPARSERCREATOR_HPP__
