#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__


#include "LazyCPP.hpp"
#include "LazyStorage.hpp"

#include "LazyGeneratedCode.hpp"
#include <vector>
#include <map>
#include <set>

class Dependance
{
public:
    Dependance();

    Dependance(uint index);
    
    void add_suboutput( LazyValue * in, uint nb);
    
    void compute_dependances();
    
    void print();
    
//     void re_init_known();    
    
    double update( uint cpt );
    
    uint index_output_ = 0;
    uint nb_sub_output_ = 0;    
    std::map< uint, LazyValue* > sub_outputs_;
    std::map< uint, std::vector< LazyValue* > > dependances_; // in case we have the value changes    
};


struct PtrComparer {
    bool operator()(const LazyOperator1* a, const LazyOperator1* b) const {
        return a < b; 
    }
    
    bool operator()(const LazyConstant* a, const LazyConstant* b) const {
        return a < b; 
    }    
    
    bool operator()(const LazyInput* a, const LazyInput* b) const {
        return a < b; 
    }        
    
    
    bool operator()(const LazyOperator2* a, const LazyOperator2* b) const {
        if (a->a_ < b->a_)  return true;
        if (a->a_ > b->a_)  return false;
        
        if (a->b_ < b->b_)  return true;
        return false;
    }
    
     bool operator()(const LazyOperatorX* a, const LazyOperatorX* b) const {
        if (a->p_.size() < b->p_.size())  return true;
        if (a->p_.size() > b->p_.size())  return false;
        return a->p_ < b->p_;
/*         
        if (a->p_.size() < b->p_.size())  return true;
        if (a->p_.size() > b->p_.size())  return false;
        
        for (int i=0;i<a->p_.size();i++)
        {
            if (a->p_[i] < b->p_[i])  return true;
            if (a->p_[i] > b->p_[i])  return false;            
        }
        return false;*/
    }   
    
};

class LazyManager
{
public:
    LazyManager();
    
    // add an instance as output
    LazyValue* add_output( LazyValue* in, uint index, uint rank );
    
    uint affect();
    
    LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_additionX( LazyValue* a , LazyValue *b);

    LazyValue* add_constant(double d);
    
    LazyInput* add_input( const double &a, const std::string& name);

    LazyValue* add_cosinus( LazyValue* a);
    
    LazyValue* add_multiplication( LazyValue* a , LazyValue *b);

    LazyValue* add_multiplicationX( LazyValue* a , LazyValue *b);

    LazyValue* add_sinus( LazyValue* a);

    LazyValue* add_soustraction( LazyValue* a , LazyValue *b);

    LazyValue* check_addition( LazyValue*a , LazyValue*b);

    LazyValue* check_multiplication( LazyValue*a , LazyValue*b);

    void clean_files();
    
    uint get_nb_inputs() const;

    LazyValue* get_zero() const;
    
    bool is_constant( LazyValue* in) const;

    bool is_input( LazyValue* in) const;
    
    bool is_minus_one(LazyValue * in) const;
    
    bool is_one(LazyValue * in) const;
    
    bool is_zero(LazyValue * in) const;

    void prepare(   const std::string& filename = "",
                    bool reuse_if_exist = false);
    
    void print_all() const;
    
    void print_all_inputs() const;

    void print_all_output_equations();
    
    void reset();
    
    void update_input();
    
    void update_input(uint index, double value);
    
    double update(uint index, uint cpt) const;
        
private:

    LazyConstant* zero_ = nullptr;
    LazyConstant*one_ = nullptr;
    LazyConstant*minus_one_ = nullptr;
    
    std::set<LazyConstant*,PtrComparer> constants_;
    std::set<LazyInput*,PtrComparer> inputs_;        
    
    std::set<LazySinus*,PtrComparer> sinus_;
    std::set<LazyCosinus*,PtrComparer> cosinus_;

    std::set<LazySoustraction*,PtrComparer> soustractions_;
    
    std::set<LazyMultiplicationX*,PtrComparer> multiplicationsX_;
    std::set<LazyAdditionX*,PtrComparer> additionsX_;

    LazyStorage additions_;
    LazyStorage multiplications_;
    
    std::map<uint,Dependance> outputs_;    

//     LazyValue* add_addition( LazyValue* a , LazyValue *b);
    
    LazyValue* add_additionX( std::list<LazyValue*> v);
    
//     LazyValue* add_multiplication( LazyValue* a , LazyValue *b);
    
    LazyValue* add_multiplicationX( std::list<LazyValue*> v);
    
//     // simplify the equation
//     LazyValue* compact( LazyValue* a);
//     
//     LazyValue * compact_additionX (LazyAdditionX *a );
//     
//     LazyValue * compact_multiplicationX (LazyMultiplicationX *a );
    
//     LazyValue * explose( LazyValue * in);
    
    std::string get_unique_name() const;
    
    void init_basic_constant();    
    
    bool is_addition(LazyValue* in) const;    
    
    bool is_additionX(LazyValue* in) const;    
    
    
    
    bool is_cosinus( LazyValue* in) const;
    
    bool is_multiplication(LazyValue* in) const;    
    
    bool is_multiplicationX(LazyValue* in) const;    
      
    bool is_sinus( LazyValue* in) const;
    
    bool is_soustraction( LazyValue* in) const;
    
    
    bool affect_ = true;
    uint counter_ = 0;
    
    std::string class_name_;
    void* handle_lib_;
    
    create_code* creator_;
    destroy_code* destructor_;
    LazyGeneratedCode* lazycode_ = nullptr;
       
};

extern LazyManager LMANAGER;

#endif // __LAZYMANAGER_HPP__
