#ifndef __LAZYVARIABLE_HPP__
#define __LAZYVARIABLE_HPP__

class LazyVariable
{
public:
    LazyVariable(){}

    LazyVariable(int & a)
    {
        ref_ = new LazyConstant(1.0*a);        
    }    
    
    LazyVariable(double & a)
    {
        ref_ = new LazyConstant(a);        
    }    
    
    LazyVariable(LazyValue & a): ref_(&a){}
        
    ~LazyVariable(){}
    
    double evaluate()
    {
        return ref_->evaluate();
    }

    inline LazyVariable& operator + (  LazyVariable& b)
    {
        LazyVariable *out = new LazyVariable();
        out->ref_ = new LazyAddition(ref_,b.ref_);
        return *out;
    }
    
    inline LazyVariable& operator - (  LazyVariable& b)
    {
        LazyVariable *out = new LazyVariable();
        out->ref_ = new LazySoustraction(ref_,b.ref_);
        return *out;
    }    
    
    inline LazyVariable& operator * (  LazyVariable& b)
    {
        LazyVariable *out = new LazyVariable();
        out->ref_ = new LazyMultiplication(ref_,b.ref_);
        return *out;
    }    
        
    LazyValue* ref_;
};

inline LazyVariable& operator + ( double a, LazyVariable& b)
{
    LazyVariable *A = new LazyVariable(a);
    return b+*A;
}

inline LazyVariable& operator + ( int  a, LazyVariable& b)
{
    LazyVariable *A = new LazyVariable(a);
    return b+*A;
}

inline LazyVariable& operator - ( LazyVariable& a , double b)
{
    LazyVariable *B = new LazyVariable(b);
    return a- *B;
}

inline LazyVariable& operator - (  LazyVariable& a , int b)
{
    LazyVariable *B = new LazyVariable(b);
    return a- *B;
}

inline LazyVariable& operator * ( LazyVariable& b, double a)
{
    LazyVariable *A = new LazyVariable(a);
    return b* *A;
}

inline LazyVariable& operator * (LazyVariable& b, int  a)
{
    LazyVariable *A = new LazyVariable(a);
    return b* *A;
}


inline LazyVariable& operator * ( double a, LazyVariable& b)
{
    LazyVariable *A = new LazyVariable(a);
    return b* *A;
}

inline LazyVariable& operator * ( int  a, LazyVariable& b)
{
    LazyVariable *A = new LazyVariable(a);
    return b* *A;
}

#endif // __LAZYVARIABLE_HPP__
