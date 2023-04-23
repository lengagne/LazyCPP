#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__

#include "LazyCPP.hpp"
#include <vector>
#include <map>

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
    LazyManager();
    
//     virtual ~LazyManager(){}
//     
    
//     
    // add an instance as output
    void add_output( LazyValue* in, uint index, uint rank );
//     
//     ///  basis operation   
//     LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_additionX( LazyValue* a , LazyValue *b);
//     
    LazyValue* add_constant(double d);
    
    LazyInput* add_input( const double &a, const std::string& name);
//     
    LazyValue* add_cosinus( LazyValue* a);
//     
//     LazyValue* add_multiplication( LazyValue* a , LazyValue *b, bool check_contraction = true);
//  
    LazyValue* add_multiplicationX( LazyValue* a , LazyValue *b);
    
    LazyValue* add_opposite(LazyValue* a );
//     
    LazyValue* add_sinus( LazyValue* a);
//     
    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);
//     
// //     void affect_value( LazyValue* in, double value);
//     
// //     double evaluate( LazyVariable&a);
    
    LazyValue* check_addition( LazyValue*a , LazyValue*b);

    LazyValue* check_multiplication( LazyValue*a , LazyValue*b);
    
//     
    uint get_nb_inputs() const;
//     
//     bool is_addition(LazyValue* in) const;
//     
    
//     

//     
    
//     
//     bool is_multiplication(LazyValue* in) const;
//     
// //     bool is_multiplicationX(LazyValue* in) const;
//     
    
//     
// //     void get_addition(LazyValue * a, std::vector<LazyValue*>& vec);
//     
// //     void get_multiplication(LazyValue * a, std::vector<LazyValue*>& vec, uint &nb_opposite);
//     
//     
    LazyValue* get_zero() const;
//     
//     inline bool is_minus_one(LazyValue * in) const
//     {
//         return in == minus_one_;
//     }    
//     
    bool is_input( LazyValue* in) const;
    
    bool is_minus_one(LazyValue * in) const;
    
    bool is_one(LazyValue * in) const;

    bool is_opposite(LazyValue* in) const;
    
    bool is_zero(LazyValue * in) const;
//     {
//         return in == zero_;
//     }
//     
//     void plot_info() const;
//     
    void prepare();
    
    void print_all_inputs() const;
//     
// //     void print_inputs();
//     
// //     void print_output_graph(uint index, uint cpt);
    
    void print_all_output_equations();
//     
    void re_init_known();
    
    void reset();
    
    double update(uint index, uint cpt);
    
    void update_all();
    
private:

    LazyConstant * zero_, *one_, *minus_one_;
    

//     
    
//     
//     
//     
    std::vector<LazyConstant*> constants_;
    std::vector<LazyInput*> inputs_;        
    
    std::vector<LazyOpposite*> opposites_;
    std::vector<LazySinus*> sinus_;
    std::vector<LazyCosinus*> cosinus_;

    std::vector<LazySoustraction*> soustractions_;
    
    std::vector<LazyMultiplicationX*> multiplicationsX_;
    std::vector<LazyAdditionX*> additionsX_;
//     
    
//     std::vector<LazyMultiplication*> multiplications_;        
//     std::vector<LazyAddition*> additions_;
    
    std::map<uint,OutDependance> dependances_;

    
    void init_basic_constant();    
    
    bool is_additionX(LazyValue* in) const;    
    
    bool is_constant( LazyValue* in) const;    
    
    bool is_multiplicationX(LazyValue* in) const;    
};




extern LazyManager LMANAGER;

#endif // __LAZYMANAGER_HPP__
