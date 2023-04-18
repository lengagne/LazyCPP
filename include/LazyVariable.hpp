#ifndef __LAZYVARIABLE_HPP__
#define __LAZYVARIABLE_HPP__

class LazyVariable
{
public:
    LazyVariable();
    
    LazyVariable(const uint & a);

    LazyVariable(const int & a);
    
    LazyVariable(const double & a);
    
    LazyVariable(const double &a, const std::string& name)
    {
        ref_ = new LazyInput(a,name);
    }
    
    LazyVariable(const std::string& name) : LazyVariable(0,name){}
    
    LazyVariable(LazyValue & a): ref_(&a){}
        
    ~LazyVariable(){}
    
//     void define_as_output(uint index);
    
    double evaluate();    
    
    double get_value() const
    {
        return ref_->get_value();
    }
    
    bool is_null() const;

    friend std::ostream& operator<< (std::ostream& stream, const LazyVariable& v)
    {
        v.ref_->print_equation();
        return stream;
    }   

    LazyVariable& operator - ( ) const;
    
    LazyVariable& operator + ( const LazyVariable& b) const;
    
    LazyVariable& operator - ( const LazyVariable& b) const;
    
    LazyVariable& operator * ( const LazyVariable& b) const;
    
    void operator += (const LazyVariable& b);
    
    void operator -= (const LazyVariable& b);
    
    void operator *= (const  LazyVariable& b);    
    
    void operator = (double val);
    
    bool operator != (const LazyVariable& b) const
    {
        return ref_ != b.ref_;
    }
    
private:
    LazyValue* ref_;
    
    friend class LazyManager;
    
    friend void LazyAddOutput(LazyVariable& in,uint index,uint rank);
    
    friend bool LazyIsInput(const LazyVariable& in);
    
    friend bool LazyIsZero(LazyValue * in);
    
    friend void LazyPrintGraph(LazyVariable& in);
    
    friend LazyVariable cos (const LazyVariable&a);
    friend LazyVariable sin (const LazyVariable&a);    
};

inline LazyVariable operator* (int a, LazyVariable& b)
{
    return LazyVariable(a)*b;
}

// LazyVariable cos (const LazyVariable&a);
// LazyVariable sin (const LazyVariable&a);



#endif // __LAZYVARIABLE_HPP__
