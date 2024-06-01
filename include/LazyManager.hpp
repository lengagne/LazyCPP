#ifndef __LAZYMANAGER_HPP__
#define __LAZYMANAGER_HPP__
#include <iostream>
#include <map>
#include <memory>
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

    bool operator()(LazyParser* a, LazyParser* b) const {    
        return compareLazyParser(a,b);
    }

    bool operator()(LazyInput* a, LazyInput* b) const {    
        return a->id_ < b->id_;
    }    
};

class LazyManager
{
public:
    LazyManager();
    
    // add an instance as output
    LazyCreator* add_output( LazyParser* in, uint index, uint rank );
    
    // the function for the creators
    LazyCreator* add_addition( LazyCreator* a , LazyCreator *b);
    
    LazyCreator* add_constant(double cst);
    
    LazyCreator* add_cosinus( LazyCreator* a);
    
    LazyCreator* add_multiplication( LazyCreator* a , LazyCreator *b);
    
    LazyCreator* add_sinus( LazyCreator* a);
    
    LazyCreator* add_soustraction( LazyCreator* a , LazyCreator *b);    
    
    void clean_files();
    
    uint get_nb_inputs() const;

    LazyParser* get_one() const;
    
    LazyParser* get_zero() const;
    
    void init_constant();
        
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

    std::set<LazyInput*,PtrComparer> inputs_;        

    std::map<uint,Dependance> outputs_;    

    LazyCreator* add_creator( LazyCreator* in);
    
    std::set<LazyCreator*,PtrComparer> creators_;
    
    std::set<LazyParser*,PtrComparer> parsers_;
    
public:
    LazyParser* add_parser( LazyParser* in);

    std::string get_unique_name() const;

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
