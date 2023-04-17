#ifndef __LAZYVARIABLE_HPP__
#define __LAZYVARIABLE_HPP__

class LazyVariable
{
public:
    LazyVariable(){}

    LazyVariable(const int & a)
    {
        ref_ = new LazyConstant(1.0*a);        
    }    
    
    LazyVariable(const double & a)
    {
        ref_ = new LazyConstant(a);        
    }    
    
    LazyVariable(const double &a, const std::string& name)
    {
        ref_ = new LazyInput(a,name);
    }
    
    LazyVariable(LazyValue & a): ref_(&a){}
        
    ~LazyVariable(){}
    
    double evaluate();    
    
    void define_as_output();
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyVariable& v)
    {
        stream<< *(v.ref_);
        return stream;
    }    

    LazyVariable& operator + ( LazyVariable& b);
    
    LazyVariable& operator - (  LazyVariable& b);
    
    LazyVariable& operator * (  LazyVariable& b);
    
    void operator = (double val);
    
private:
    LazyValue* ref_;
    
    friend class LazyManager;
    
    friend void AddLazyOutput(LazyVariable& in);
    
    friend void PrintGraph(LazyVariable& in);
};



#endif // __LAZYVARIABLE_HPP__
