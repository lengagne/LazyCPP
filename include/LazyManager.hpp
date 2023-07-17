#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__


#include "LazyCPP.hpp"
#include "LazyStorage.hpp"

#include "LazyGeneratedCode.hpp"
#include <vector>
#include <map>

#define TEST_STORAGE 1
#define COUNTER 1

// #define Change std::vector<LazyInput*>
class Dependance
{
public:
    Dependance();

    Dependance(uint index);
    
    void add_suboutput( LazyValue * in, uint nb);
    
    void compute_dependances();
    
    void print();
    
    double update( uint cpt );
    
    
    uint index_output_ = 0;
    uint nb_sub_output_ = 0;    
    std::map< uint, LazyValue* > sub_outputs_;
    std::map< uint, std::vector< LazyValue* > > dependances_; // in case we have the value changes    
};




class LazyManager
{
public:
    LazyManager();
    
    // add an instance as output
    LazyValue* add_output( LazyValue* in, uint index, uint rank );
    
    uint affect();
    
    LazyValue* add_additionX( LazyValue* a , LazyValue *b);

    LazyValue* add_constant(double d);
    
    LazyInput* add_input( const double &a, const std::string& name);

    LazyValue* add_cosinus( LazyValue* a);

    LazyValue* add_multiplicationX( LazyValue* a , LazyValue *b);

    LazyValue* add_sinus( LazyValue* a);

    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);

    LazyValue* check_addition( LazyValue*a , LazyValue*b);

    LazyValue* check_multiplication( LazyValue*a , LazyValue*b);

    uint get_nb_inputs() const;

    LazyValue* get_zero() const;

    bool is_input( LazyValue* in) const;
    
    bool is_minus_one(LazyValue * in) const;
    
    bool is_one(LazyValue * in) const;
    
    bool is_zero(LazyValue * in) const;

    void prepare();
    
    void print_all_inputs() const;

    void print_all_output_equations();

    void re_init_known();
    
    void reset();
    
    double update(uint index, uint cpt);
    
//     void update_all();
    
private:

    LazyConstant * zero_, *one_, *minus_one_;
    
    std::vector<LazyConstant*> constants_;
    std::vector<LazyInput*> inputs_;        
    
    std::vector<LazySinus*> sinus_;
    std::vector<LazyCosinus*> cosinus_;

    std::vector<LazySoustraction*> soustractions_;
    
    std::vector<LazyMultiplicationX*> multiplicationsX_;
    std::vector<LazyAdditionX*> additionsX_;

#ifdef TEST_STORAGE
    LazyStorage additions_;
    LazyStorage multiplications_;
#else
    std::vector<LazyAddition*> additions_;    
    std::vector<LazyMultiplication*> multiplications_;        

#endif
    
    std::map<uint,Dependance> outputs_;    

    LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_additionX( std::list<LazyValue*> v);
    
    LazyValue* add_multiplication( LazyValue* a , LazyValue *b);
    
    LazyValue* add_multiplicationX( std::list<LazyValue*> v);
    
    // simplify the equation
    LazyValue* compact( LazyValue* a);
    
    LazyValue * compact_additionX (LazyAdditionX *a );
    
    LazyValue * compact_multiplicationX (LazyMultiplicationX *a );

//     void detect_input_change();
    
    LazyValue * explose( LazyValue * in);
    
    void init_basic_constant();    
    
    bool is_additionX(LazyValue* in) const;    
    
    bool is_constant( LazyValue* in) const;
    
    bool is_cosinus( LazyValue* in) const;
    
    bool is_multiplicationX(LazyValue* in) const;    
      
    bool is_sinus( LazyValue* in) const;
    
    bool is_soustraction( LazyValue* in) const;
    
    
    bool affect_ = true;
    uint counter_ = 0;
    
//     Change current_change_;
    
    create_code* creator_;
    destroy_code* destructor_;
    LazyGeneratedCode* lazycode_ = nullptr;
    
};

extern LazyManager LMANAGER;

#endif // __LAZYMANAGER_HPP__
