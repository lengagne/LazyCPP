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
    
    double evaluate();    
    
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
    
    friend void PrintGraph(LazyVariable& in);
};



// inline LazyVariable& operator + ( double a, LazyVariable& b)
// {
//     LazyVariable *A = new LazyVariable(a);
//     return b+*A;
// }
// 
// inline LazyVariable& operator + ( int  a, LazyVariable& b)
// {
//     LazyVariable *A = new LazyVariable(a);
//     return b+*A;
// }
// 
// inline LazyVariable& operator - ( LazyVariable& a , double b)
// {
//     LazyVariable *B = new LazyVariable(b);
//     return a- *B;
// }
// 
// inline LazyVariable& operator - (  LazyVariable& a , int b)
// {
//     LazyVariable *B = new LazyVariable(b);
//     return a- *B;
// }
// 
// inline LazyVariable& operator * ( LazyVariable& b, double a)
// {
//     LazyVariable *A = new LazyVariable(a);
//     return b* *A;
// }
// 
// inline LazyVariable& operator * (LazyVariable& b, int  a)
// {
//     LazyVariable *A = new LazyVariable(a);
//     return b* *A;
// }
// 
// 
// inline LazyVariable& operator * ( double a, LazyVariable& b)
// {
//     LazyVariable *A = new LazyVariable(a);
//     return b* *A;
// }
// 
// inline LazyVariable& operator * ( int  a, LazyVariable& b)
// {
//     LazyVariable *A = new LazyVariable(a);
//     return b* *A;
// }

#endif // __LAZYVARIABLE_HPP__
