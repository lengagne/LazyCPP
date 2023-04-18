#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__

#include "LazyCPP.hpp"
#include <vector>

// struct InputDependancies
// {
//     std::vector<LazyInput*> inputs_;
//     uint max_index_;
//     uint update_index_;
// };


class LazyManager
{
public:
    LazyManager(){
//         zero_ = new LazyConstant(0.0);        
//         one_ = new LazyConstant(1.0);
    }
    
    virtual ~LazyManager(){}
    
    void add_input( LazyInput* in);
    
    // add an instance as output
    void add_output( LazyValue* in);

    
    ///  basis operation
    
    LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_cosinus( LazyValue* a);
    
    LazyValue* add_multiplication( LazyValue* a , LazyValue *b);
    
    LazyValue* add_sinus( LazyValue* a);
    
    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);
    
    void affect_value( LazyValue* in, double value);
    
//     double evaluate( LazyVariable&a);
    
    uint get_nb_inputs() const
    {
        return inputs_.size();
    }
    
    uint get_nb_outputs() const
    {
        return outputs_.size();
    }
    
//     LazyValue* get_zero() const
//     {
//         return zero_;
//     }
//     
//     bool is_zero(LazyValue * in) const
//     {
//         return in == zero_;
//     }
    
    void prepare();
    
    void print_inputs();
    
    void re_init_known();
    
    void reset();
    
    void update_all();
    
    double update(uint index);
    
    friend void LazyAddOutput(LazyVariable& in);
    
    friend void LazyGetInfo();    
    
    friend void LazyPrintGraph(LazyVariable& in);
    
private:

//     LazyConstant * zero_, *one_;
    
    std::vector<LazyInput*> inputs_;    
    std::vector<LazyAddition*> additions_;
    std::vector<LazyCosinus*> cosinus_;
    std::vector<LazyMultiplication*> multiplications_;        
    std::vector<LazySinus*> sinus_;
    std::vector<LazySoustraction*> soustractions_;
    std::vector< std::vector< LazyValue* > > output_dependances_;
    
    std::vector< LazyValue* > outputs_;
    
//     bool state_ = true;    // 0 for assignation, 1 for evaluation
//     uint nb_process_=0;
    uint nb_outputs_ = 0;
    
};




#endif // __LAZYMANAGER_HPP__
