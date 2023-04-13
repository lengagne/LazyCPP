#ifndef __LAZYCPP_H__
#define __LAZYCPP_H__

class LazyValue
{
public:
    
    virtual ~LazyValue(){}
    
    virtual double evaluate() = 0;    
    
    friend std::ostream& operator<< (std::ostream& stream, const LazyValue& v)
    {
        stream<<v.value_;
        return stream;
    }
    
    double value_;
};

class LazyInput : public LazyValue {
public:
    LazyInput(double value) {value_ = value;}
    double evaluate() { return value_; }
    void operator = (const double & d)
    {
        value_ = d;
    }
        
private:
};

class LazyConstant : public LazyValue {
public:
    LazyConstant(double value){value_ = value;}
    double evaluate() { return value_; }
    void operator = (const double & d)
    {
        value_ = d;
    }
        
private:
};


class LazyAddition : public LazyValue {
public:
    LazyAddition(LazyValue* a, LazyValue* b) : a_(a), b_(b) {
        value_ = a->value_+b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() + b_->evaluate();
        return value_;
    }
    
private:
    LazyValue* a_;
    LazyValue* b_;
};

class LazyMultiplication : public LazyValue {
public:
    LazyMultiplication(LazyValue* a, LazyValue* b) : a_(a), b_(b) {
        value_ = a->value_*b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() * b_->evaluate();
        return value_;
    }
    
private:
    LazyValue* a_;
    LazyValue* b_;
};

class LazySoustraction : public LazyValue {
public:
    LazySoustraction(LazyValue* a, LazyValue* b) : a_(a), b_(b) {
        value_ = a->value_-b->value_;        
    }
    
    double evaluate() {
        value_ = a_->evaluate() - b_->evaluate();
        return value_;
    }
    
private:
    LazyValue* a_;
    LazyValue* b_;
};


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


#endif // __LAZYCPP_H__
