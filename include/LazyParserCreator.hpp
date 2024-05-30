#ifndef __LAZYPARSERCREATOR_HPP__
#define __LAZYPARSERCREATOR_HPP__

#include "LazyCreator.hpp"
#include "LazyParser.hpp"

class LazyParserCreator : public LazyParser, public LazyCreator
{
public:
    
    
    virtual LazyCreator* explose() =0;
    
    virtual std::string get_equation( )
    {
        return get_name();
    }
    
    
    virtual bool is_zero() const
    {
        return false;
    }
protected:    
    
private:

};


#endif //  __LAZYPARSERCREATOR_HPP__
