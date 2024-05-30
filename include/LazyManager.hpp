#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__
#include <iostream>
#include <map>
#include <set>
#include <vector>


#include "LazyCPP.hpp"

#include "LazyGeneratedCode.hpp"


class Dependance
{
public:
    Dependance();

    Dependance(uint index);
    
    void add_suboutput( LazyCreator* in, uint nb);
    
    void compute_dependances();
    
    void print();
    
//     void re_init_known();    
    
    double update( uint cpt );
    
    uint index_output_ = 0;
    uint nb_sub_output_ = 0;    
    std::map< uint, LazyCreator* > sub_outputs_;
    std::map< uint, std::vector< LazyCreator* > > dependances_; // in case we have the value changes    
};


struct PtrComparer {
    
    bool operator()(LazyCreator* a, LazyCreator* b) const {    
        return compareLazyCreator(a,b);
    }

    bool operator()(const LazyParser* a, const LazyParser* b) const {    
        return compareLazyParser(a,b);
    }

    bool operator()(const LazyInput* a, const LazyInput* b) const {    
        return a->name_ < b->name_;
    }    
//     bool operator()(const LazyValue* a, const LazyValue* b) const {    
//         std::cout<<"PtrComparer LazyValue* a = "<< *a <<std::endl;
//         std::cout<<"PtrComparer LazyValue* b = "<< *b <<std::endl;
//         if (a->type_ == b->type_)
//         {
//             return a->id_ < b->id_; 
//         }
//         return  a->type_ <  b->type_;      
//     }    
//     
//     bool operator()(const LazyOperator1* a, const LazyOperator1* b) const {
//         return a < b; 
//     }
    
//     bool operator()(const LazyConstant* a, const LazyConstant* b) const {
//         return a < b; 
//     }    
    
/*    bool operator()(const LazyInput* a, const LazyInput* b) const {
//         return a < b; 
        if (a->id_ == b->id_)
        {
            if (a->name_ == b->name_)
            {
                return a < b; 
            }
            return  a->name_ <  b->name_;   
        }
        return  a <  b;          
    }   */     
    
    
//     bool operator()(const LazyOperator2* a, const LazyOperator2* b) const {
//         if (a->a_ < b->a_)  return true;
//         if (a->a_ > b->a_)  return false;
//         
//         if (a->b_ < b->b_)  return true;
//         return false;
//     }
    
//      bool operator()(const LazyOperatorX* a, const LazyOperatorX* b) const {
//         if (a->p_.size() < b->p_.size())  return true;
//         if (a->p_.size() > b->p_.size())  return false;
//         return a->p_ < b->p_;
/*         
        if (a->p_.size() < b->p_.size())  return true;
        if (a->p_.size() > b->p_.size())  return false;
        
        for (int i=0;i<a->p_.size();i++)
        {
            if (a->p_[i] < b->p_[i])  return true;
            if (a->p_[i] > b->p_[i])  return false;            
        }
        return false;*/
//     }   
    
};

class LazyManager
{
public:
    LazyManager();
    
    // add an instance as output
    LazyCreator* add_output( LazyParser* in, uint index, uint rank );
    
//     uint affect();
    
    // the function for the creators
    LazyCreator* add_addition( LazyCreator* a , LazyCreator *b);
    
    LazyCreator* add_constant(double cst);
    
    LazyCreator* add_cosinus( LazyCreator* a);
    
    LazyCreator* add_multiplication( LazyCreator* a , LazyCreator *b);
    
    LazyCreator* add_sinus( LazyCreator* a);
    
    LazyCreator* add_soustraction( LazyCreator* a , LazyCreator *b);    
    

//     LazyValue* check_addition( LazyValue*a , LazyValue*b);

//     LazyValue* check_multiplication( LazyValue*a , LazyValue*b);

    void clean_files();
    
    uint get_nb_inputs() const;

    LazyParser* get_one() const;
    
    LazyParser* get_zero() const;
    
//     bool is_constant( LazyValue* in) const;

//     bool is_input( LazyValue* in) const;
    
//     bool is_minus_one(LazyValue * in) const;
    
    bool is_one(LazyParser * in) const;
    
    bool is_zero(LazyParser * in) const;

    void prepare( const std::string& filename = "",
                    bool reuse_if_exist = false);
    
    void print_all() const;
    
    void print_all_inputs() const;

    void print_all_output_equations();
    
    void reset();
    
    void update_input();
    
    void update_input(uint index, double value);
    
    double update(uint index, uint cpt) const;
        

    // the function for the parsers
    LazyParser* add_additionX( LazyParser* a , LazyParser *b);
    
    LazyParser* add_additionX( LazyParser* a , double value);

    LazyParser* add_constant_parser( double val);
    
    LazyParser* add_cosinus( LazyParser* a);
    
    LazyParser* add_input( const double &a, const std::string& name);

    LazyParser* add_multiplicationX( LazyParser* a , LazyParser *b);

    LazyParser* add_sinus( LazyParser* a);
    
private:
    
    LazyParser* zero_ = nullptr;
    LazyParser* one_ = nullptr;
    
    LazyCreator* czero_ = nullptr;
    LazyCreator* cone_ = nullptr;
//     LazyConstant*minus_one_ = nullptr;
//     
//     std::set<LazyConstant*,PtrComparer> constants_;
    std::set<LazyInput*,PtrComparer> inputs_;        
//     
//     std::set<LazySinus*,PtrComparer> sinus_;
//     std::set<LazyCosinus*,PtrComparer> cosinus_;
// 
//     std::set<LazySoustraction*,PtrComparer> soustractions_;
//     
//     std::set<LazyMultiplicationX*,PtrComparer> multiplicationsX_;
//     std::set<LazyAdditionX*,PtrComparer> additionsX_;
// 
//     std::set<LazyAddition*,PtrComparer> additions_;
//     std::set<LazyMultiplication*,PtrComparer> multiplications_;
// //     LazyStorage additions_;
// //     LazyStorage multiplications_;
//     
    std::map<uint,Dependance> outputs_;    
// 
// // //     LazyValue* add_addition( LazyValue* a , LazyValue *b);

    LazyCreator* add_creator( LazyCreator* in);
    
    std::set<LazyCreator*,PtrComparer> creators_;
    
    std::set<LazyParser*,PtrComparer> parsers_;
    
public:
    LazyParser* add_parser( LazyParser* in);
//     LazyValue* add_additionX( std::list<LazyValue*> v);
//     
// //     LazyValue* add_multiplication( LazyValue* a , LazyValue *b);
    
//     LazyValue* add_multiplicationX( std::list<LazyValue*> v);
//     
// private:
// //     // simplify the equation
// //     LazyValue* compact( LazyValue* a);
// //     
// //     LazyValue * compact_additionX (LazyAdditionX *a );
// //     
// //     LazyValue * compact_multiplicationX (LazyMultiplicationX *a );
//     
// //     LazyValue * explose( LazyValue * in);
//     
    std::string get_unique_name() const;
//     
//     void init_basic_constant();    
//     
//     bool is_addition(LazyValue* in) const;    
//     
//     bool is_additionX(LazyValue* in) const;    
//     
//     
//     
//     bool is_cosinus( LazyValue* in) const;
//     
//     bool is_multiplication(LazyValue* in) const;    
//     
//     bool is_multiplicationX(LazyValue* in) const;    
//       
//     bool is_sinus( LazyValue* in) const;
//     
// //     bool is_soustraction( LazyValue* in) const;
//     
//     
//     bool affect_ = true;
//     uint counter_ = 0;

    std::string class_name_;
    void* handle_lib_;
       
    create_code* creator_;
    destroy_code* destructor_;
    LazyGeneratedCode* lazycode_ = nullptr;
    
    friend class LazyVariable;
    
    
    int dummy_debug =0 ;
       
};

extern LazyManager LMANAGER;

#endif // __LAZYMANAGER_HPP__
