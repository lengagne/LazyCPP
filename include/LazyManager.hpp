#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__

#include "LazyCPP.hpp"
#include <vector>
#include <map>

// struct InputDependancies
// {
//     std::vector<LazyInput*> inputs_;
//     uint max_index_;
//     uint update_index_;
// };

struct OutDependance
{
    uint index=0;
    uint nb_outputs_ = 0;
    std::map< uint, LazyValue* > outputs;
    std::map< uint, std::vector< LazyValue* > > output_dependances;
};


class LazyManager
{
public:
    LazyManager(){
        zero_ = new LazyConstant(0.0);   
        one_ = new LazyConstant(1.0);
        minus_one_ = new LazyConstant(-1.0);
        init_basic_constant();
    }
    
    virtual ~LazyManager(){}
    
    void add_input( LazyInput* in);
    
    // add an instance as output
    void add_output( LazyValue* in, uint index, uint rank );

    
    ///  basis operation
    
    LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_constant(double d);
    
    LazyValue* add_cosinus( LazyValue* a);
    
    LazyValue* add_multiplication( LazyValue* a , LazyValue *b, bool check_contraction = true);
    
    LazyValue* add_opposite(LazyValue* a );
    
    LazyValue* add_sinus( LazyValue* a);
    
    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);
    
//     void affect_value( LazyValue* in, double value);
    
//     double evaluate( LazyVariable&a);
    void init_basic_constant()
    {             
        constants_.push_back(zero_);
        constants_.push_back(one_);
        constants_.push_back(minus_one_);        
    }
    
    uint get_nb_inputs() const
    {
        return inputs_.size();
    }
    
    bool is_addition(LazyValue* in) const;
    
//     bool is_additionX(LazyValue* in) const;
    
    bool is_constant( LazyValue* in) const;
    
    bool is_input( LazyValue* in) const;
    
    bool is_multiplication(LazyValue* in) const;
    
//     bool is_multiplicationX(LazyValue* in) const;
    
    bool is_opposite(LazyValue* in) const;
    
    void get_addition(LazyValue * a, std::vector<LazyValue*>& vec);
    
    void get_multiplication(LazyValue * a, std::vector<LazyValue*>& vec, uint &nb_opposite);
    
    
    inline LazyValue* get_zero() const
    {
        return zero_;
    }
    
    inline bool is_minus_one(LazyValue * in) const
    {
        return in == minus_one_;
    }    
    
    inline bool is_one(LazyValue * in) const
    {
        return in == one_;
    }    
    
    inline bool is_zero(LazyValue * in) const
    {
        return in == zero_;
    }
    
    void plot_info() const;
    
    void prepare();
    
    void print_inputs();
    
    void print_output_graph(uint index, uint cpt);
    
    void re_init_known();
    
    void reset();
    
//     void simplify(LazyMultiplicationX* v);
    
    void update_all();
    
    double update(uint index, uint cpt);
    
    friend void LazyAddOutput(uint index, LazyVariable& in);
    
    friend void LazyPrintGraph(LazyVariable& in);
    
private:

    LazyConstant * zero_, *one_, *minus_one_;
    
    std::vector<LazyInput*> inputs_;    
    std::vector<LazyAddition*> additions_;
    std::vector<LazyCosinus*> cosinus_;
    std::vector<LazyMultiplication*> multiplications_;        
    std::vector<LazySinus*> sinus_;
    std::vector<LazySoustraction*> soustractions_;
    std::vector<LazyConstant*> constants_;
    std::vector<LazyOpposite*> opposites_;
    
//     std::vector<LazyMultiplicationX*> multiplicationsX_;
//     std::vector<LazyAdditionX*> additionsX_;
    
    std::map<uint,OutDependance> dependances_;

//     uint nb_groups_ = 0;
    
//     bool contract = true;
//     bool contract_add = false;
//     bool simplify_ = true;
    
};




#endif // __LAZYMANAGER_HPP__
