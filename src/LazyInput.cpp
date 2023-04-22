#include "LazyInput.hpp"


LazyInput::LazyInput(double value, const std::string name):name_(name) 
{            
    value_ = value;
    known_ = true;
}
