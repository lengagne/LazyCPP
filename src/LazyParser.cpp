#include "LazyParser.hpp"

bool compareLazyParser(const LazyParser* a,
                        const LazyParser* b)
{
    if (a->typep_ != b->typep_)
    {
        // FIXME
        return (a->typep_ < b->typep_);
    }else
    {
        return (a>b);
    }
}

std::ostream& operator<< (std::ostream& stream, const LazyParser& v)
{
//     v.ref_->print_equation();
//     stream << v.ref_->value_;
    stream <<"[TYPE: "<< v.typep_ <<" : "<<   v.get_name()<< "]";
    return stream;
}
   
