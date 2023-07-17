#include "LazyManager.hpp"
#include <algorithm>
#include <fstream>
#include "config_LazyCPP.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/time.h>

double get_cpu_time(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + 1e-6 * t.tv_usec;
//    return (double)clock() / CLOCKS_PER_SEC;
}

Dependance::Dependance()
{
    index_output_ = 42;
    nb_sub_output_ = 0;
};

Dependance::Dependance(uint index)
{
    index_output_ = index;
    nb_sub_output_ = 0;
};

void Dependance::add_suboutput( LazyValue * in, uint nb)
{
    sub_outputs_[nb] = in;
}

void Dependance::compute_dependances()
{
    uint cpt = 0;
    uint counter = 0;
    std::vector< LazyValue* > vec;
    for (auto out : sub_outputs_)
    {
//         std::cout<<"Sub output  ";
        out.second->add_to_list(vec);
//         std::cout<<" add "<< vec.size()<<std::endl;
        dependances_[cpt++] = vec;
        counter += vec.size();
    }
//     std::cout<<" counter = "<< counter <<std::endl;
}

void Dependance::print()
{
    for (auto idep : sub_outputs_)
    {
        std::cout<<"output : ";
        idep.second->print();
        std::cout<<"\n";
    }        
}

inline double Dependance::update( uint cpt )
{        
    std::vector<LazyValue*>& suboutput = dependances_[cpt];
    for (LazyValue * i : suboutput)
    {
        i->compute();
    }
    return sub_outputs_[cpt]->get_value();
}


LazyManager::LazyManager()
{
    zero_ = new LazyConstant(0.0);   
    one_ = new LazyConstant(1.0);
    minus_one_ = new LazyConstant(-1.0);
    init_basic_constant();
}

LazyValue* LazyManager::add_additionX( LazyValue* a , LazyValue *b)
{
    LazyValue* check = check_addition(a,b);
    if (check)
        return check;    
    
    std::list<LazyValue*> vec;
    if (is_additionX(a))
    {
        LazyAdditionX *A = (LazyAdditionX*) a;
        for (auto& iter : A->p_) if (! is_zero(iter))
            vec.push_back(iter);
    }else
        vec.push_back(a);
        
    if (is_additionX(b))
    {
        LazyAdditionX *B = (LazyAdditionX*) b;
        for (auto& iter : B->p_)if (! is_zero(iter))
            vec.push_back(iter);    
    }else
        vec.push_back(b);
    
    // creation of the new object
    LazyAdditionX* out = new LazyAdditionX(vec);
    
    // check if does not already exist
    for (auto& iter : additionsX_)
        if (*iter == *out)
            return iter;
    additionsX_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_constant( double d)
{
    for (auto& iter : constants_)
        if(iter->value_ == d)
        {
            return iter;
        }
    LazyConstant * out = new LazyConstant(d);
    constants_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_cosinus( LazyValue* a)
{
    LazyCosinus* out = new LazyCosinus(a);
    // check if does not already exist
    for (auto& iter : cosinus_)
        if (*iter == *out)
            return iter;
    cosinus_.push_back(out);
    return out;
}

LazyInput* LazyManager::add_input( const double &a, const std::string& name)
{
    for (auto& iter : inputs_)
        if(iter->name_ == name)
        {
            iter->value_ = a;
            return iter;
        }
        
    LazyInput* out = new LazyInput(a,name);
    inputs_.push_back(out);
    return out;
}

LazyValue* LazyManager::add_multiplicationX( LazyValue* a , LazyValue *b)
{
    LazyValue* check = check_multiplication(a,b);
    if (check)
        return check;
    
    std::list<LazyValue*> vec;
    if (is_multiplicationX(a))
    {
        LazyMultiplicationX *A = (LazyMultiplicationX*) a;
        for (auto& iter : A->p_) if (! is_one(iter))
            vec.push_back(iter);
    }else
        vec.push_back(a);
        
    if (is_multiplicationX(b))
    {
        LazyMultiplicationX *B = (LazyMultiplicationX*) b;
        for (auto& iter : B->p_) if (! is_one(iter))
            vec.push_back(iter);    
    }else
        vec.push_back(b);
    
    return add_multiplicationX(vec);
}

LazyValue* LazyManager::add_output( LazyValue* in, uint index, uint rank )
{
    // FIXME : on ne dit rien si ca existe deja
    if (outputs_.find(index) == outputs_.end())
    { // there is no such element, we create it
        outputs_[index] = Dependance(index);    
    }   

    LazyValue *output = explose(compact(in));
    outputs_[index].add_suboutput(output,rank);
    return output;
}

LazyValue* LazyManager::add_sinus( LazyValue* a)
{
    LazySinus* out = new LazySinus(a);
    // check if does not already exist
    for (auto& iter : sinus_)
        if (*iter == *out)
            return iter;
    sinus_.push_back(out);
    return out;
}


LazyValue* LazyManager::add_soustraction( LazyValue* a , LazyValue *b)
{
    if (a == b)
    {
        return zero_;
    }
    
    if (is_zero(b))
    {
        return a;
    }    

    if (is_zero(a))
    {
        return add_multiplicationX(b,minus_one_);
    }    
    
    LazySoustraction* out = new LazySoustraction(a,b);
    for (int i=0;i<soustractions_.size();i++)
    {
        if (*soustractions_[i] == *out)
        {
            delete out;
            return soustractions_[i];
        }
    }        
    soustractions_.push_back(out);
    return out;
}

uint LazyManager::affect()
{
    affect_ = true;
    return counter_;
}

LazyValue* LazyManager::check_addition( LazyValue*a , LazyValue*b)
{            
    if ( is_zero(a))
        return b;
    
    if ( is_zero(b))
        return a;

    if (is_minus_one(a))
    {
        return add_soustraction(b,a);
    }

    if (is_minus_one(b))
    {
        return add_soustraction(a,b);
    }  
    
    return 0;
}


LazyValue* LazyManager::check_multiplication( LazyValue*a , LazyValue*b)
{        
    if ( is_zero(a) || is_zero(b))
        return zero_;
    
    if ( is_one(a))
        return b;
    
    if ( is_one(b))
        return a;
    
    if (is_constant(a) && is_constant(b))
    {
        return add_constant( a->value_*b->value_);
    }
    
    return 0;
}

uint LazyManager::get_nb_inputs() const
{
    return inputs_.size();
}

LazyValue* LazyManager::get_zero() const
{
    return zero_;
}

bool LazyManager::is_input( LazyValue* in) const
{
    for (auto& iter : inputs_)
        if (iter == in)
            return true;
    return false;
}

bool LazyManager::is_minus_one(LazyValue * in) const
{
    return in == minus_one_;
}    

bool LazyManager::is_one(LazyValue * in) const
{
    return in == one_;
}

bool LazyManager::is_zero(LazyValue * in) const
{
    return in == zero_;
}

void LazyManager::prepare()
{
//     print_all_inputs();
    for (auto& iter : outputs_)
    {
        re_init_known();  
        iter.second.compute_dependances();
    }
    
//     std::cout<<"LazyManager::prepare() creating files"<<std::endl;
    std::string filename = "LazyCPPGenerated.cpp";
    std::string command = "rm -f "+ filename;
    int dummy = system ( command.c_str() );
    
    std::ofstream f (filename );

    std::string class_name_  = filename;
    class_name_.erase(class_name_.find_last_of("."), std::string::npos);
    f<<"#include <vector>\n#include <math.h>\n#include <iostream>\n#include \"LazyGeneratedCode.hpp\" \n\n\n";
    f<<"class "<<class_name_<<": public LazyGeneratedCode\n{\npublic:\n";

    f<<"\tunsigned int get_nb_in()const \n\t{\n\t\treturn "<< get_nb_inputs() <<";\n\t}\n\n";
    f<<"\t // intermediate variables\n";


    uint LazyCounter = 0;
    
    // on numerote les entrées 
    for (auto & iter : inputs_)
    {
        iter->id_ = LazyCounter++;
    }
    
    uint nb_in = LazyCounter;
    // on numerote les variables intermédiaires.
    for (auto& iter : outputs_) // pour toutes les sorties
    {
        for ( auto& it2 : iter.second.dependances_) // pour toutes les sous sorties
        {
            for(auto & it3 : it2.second)    // pour toutes les dépendances
            {
                if (it3->id_ == -1)
                {
                    it3->id_ = LazyCounter++;
                }
            }
        }
    }
//     std::cout<<"on a " << nb_in <<" entrées "<<std::endl;
//     std::cout<<"on a " << LazyCounter <<" variables "<<std::endl;
    
    
    f<<"\t"<<RealName<<" t["<<nb_in<<"];\n";        
    f<<"\t"<<RealName<<" x["<<LazyCounter<<"];\n";      
    
    f<<"\n\n\tvoid set_input(std::vector<"<< RealName<<"> & in)\n\t{\n";
    for (auto & iter : inputs_)
    {
              f<< "\t\tx["<< iter->id_ <<"] =  in["<<iter->id_ <<"];"<<std::endl;
    }
    f<<"\t}\n\n";
    
    f<<"\t"<< RealName<<" function(unsigned int out, unsigned int index=0)\n\t{\n\t\tswitch(out)\n\t\t{\n";
    
    for (auto& iter : outputs_)
    {
        // on remet à zéro la mémoire des variables
        for ( auto& it2 : iter.second.dependances_)
            for(auto & it3 : it2.second)
                it3->update_ = true;
    
        
        
        f<<"\t\t\tcase("<<iter.first <<"): // out number "<< iter.first <<" \n";
        f<<"\t\t\t\tswitch(index)\n\t\t\t\t{\n";
        for ( auto& it2 : iter.second.dependances_)
        {
            f<<"\t\t\t\t\t case("<< it2.first<<"): " <<std::endl;
            for(auto & it3 : it2.second)    if (it3->update_)
            {
                f<< "\t\t\t\t\t"<<   it3->file_print("x")  <<";\n";
                it3->update_ = false;
            }
            
            f<<"\t\t\t\t\treturn x["+ std::to_string(iter.second.sub_outputs_[ it2.first]->id_) +"];\n" <<std::endl;
        }
        f<<"\t\t\t\t\tdefault: return 0.;\n\t\t\t\t};\n";
        f<<"\t\t\t\tbreak;\n";            
    }    
    f<<"\t\t\tdefault: return 0.;\n";
    f<<"\n\t\t}\n\t}\n};\n\n";
    f<<"extern \"C\" " + class_name_ +"* create()\n{\n\treturn new " + class_name_ + "();\n}\n\n";
    f<<"extern \"C\" void destroy(" + class_name_ +"* p)\n{\n\tdelete p;\n}\n\n";

    f.close();   
    
//     std::cout<<"LazyManager::prepare() compilation"<<std::endl;
    
    double tsart  = get_cpu_time();
    // Create the library
    command = "g++ -O3 -ggdb -shared " + filename + std::string( COMPILE_FLAGS) + " -I"  + " " + std::string( INCLUDE_DIR) + " -o lib"+class_name_+".so -fPIC";
//    std::cout<<"Compilation command is : "<< command<<std::endl;
    dummy = system ( command.c_str() );
//    std::cout<<"ComputedTreeList::prepare_file step 6"<<std::endl;    
    double compilation_time = get_cpu_time() - tsart;
    std::cout<<"compilation_time = " << compilation_time <<std::endl;
    
//     std::cout<<"LazyManager::prepare() Load compiled library"<<std::endl;
    
    std::string lib;
//     if (libname =="")
        lib = "./lib"+class_name_ +".so";
//     else
//         lib = libname;

    unsigned int count = 0;
    void* library;
    do{
        count++;
        library =dlopen(lib.c_str(), RTLD_LAZY);
        if (!library) {
            std::cerr <<"Error1 in "<<__FILE__<<" at line "<<__LINE__<< " : Cannot load library ("<< lib <<"), with the error : " << dlerror() << '\n';
            if(count>10)
            {
                std::cerr<<"Cannot load the library, stopping program"<<std::endl;
                std::cerr<<"Sometimes the following line solve the issue : \n export LD_LIBRARY_PATH=."<<std::endl;
                exit(0);
            }
            sleep(1);
        }
    }while(!library);
    // load the symbols
    count = 0;
    do{
        count++;
        creator_ = (create_code*) dlsym(library, "create");
        destructor_ = (destroy_code*) dlsym(library, "destroy");
        if (!creator_ || !destructor_)
        {
            std::cerr <<"Error2 in "<<__FILE__<<" at line "<<__LINE__<< " : Cannot load symbols of ("<< lib <<"), with the error : " << dlerror() << '\n';
            if(count>10)
                exit(0);
            sleep(1);
        }
    }while(!creator_ || ! destructor_);

    lazycode_ = creator_(); 
    
}

void LazyManager::print_all_inputs() const
{
    for (auto& iter : inputs_)
    {
        std::cout<<" input : "<< iter->name_<<std::endl;
    }
}

void LazyManager::print_all_output_equations()
{
//     for (auto iter = outputs_.begin(); iter != outputs_.end(); ++iter)
    for (auto& iter : outputs_)
    {
        iter.second.print();
//         Dependance& dep = iter.second;
//         for (auto idep =dep.outputs.begin(); idep != dep.outputs.end(); idep++)
//         {
//             std::cout<<"output : ";
//             idep->second->print();
//             std::cout<<"\n";
//         }
    }
}

void LazyManager::re_init_known()
{
//     for (auto iter : additions_)   iter->re_init_known();
    for (auto& iter : additionsX_)   iter->re_init_known();
    for (auto& iter : soustractions_)   iter->re_init_known();
//     for (auto& iter : multiplications_)   iter->re_init_known();
    for (auto& iter : multiplicationsX_)   iter->re_init_known();
    for (auto& iter : cosinus_)   iter->re_init_known();
    for (auto& iter : sinus_)   iter->re_init_known();
}

void LazyManager::reset()
{
    inputs_.clear();
    additionsX_.clear();
//     additions_.clear();
    cosinus_.clear();
//     multiplications_.clear();
    multiplicationsX_.clear();
    sinus_.clear();
    soustractions_.clear();
    constants_.clear();
    init_basic_constant();
    counter_ = 0;
    affect_ = false;
    
    
    outputs_.clear();
}

double LazyManager::update(uint index, uint cpt)
{
    std::vector<double> inputs(inputs_.size());
    for (auto & iter : inputs_)
    {
        inputs[iter->id_] = iter->value_;
    }
    
    lazycode_->set_input(inputs);
    return lazycode_->function(index,cpt);

//     return outputs_[index].update(cpt);
}

/////////////////////////////////////////////////////
////////////////////Private functions ///////////////
/////////////////////////////////////////////////////

LazyValue* LazyManager::add_addition( LazyValue* a , LazyValue *b)
{
    LazyValue* check = check_addition(a,b);
    if (check)
        return check;
    
    LazyAddition* out = new LazyAddition(a,b);
    LazyOperator2* tmp = (LazyOperator2*) out;
    if ( additions_.look_for (&tmp) )
    {
//         std::cout<<"already found addition"<<std::endl;
        return tmp;
    }
    additions_.store(tmp);
    return tmp;
}

LazyValue* LazyManager::add_additionX( std::list<LazyValue*> v)
{
    // creation of the new object
    LazyAdditionX* out = new LazyAdditionX(v);
    
    // check if does not already exist
    for (auto& iter : additionsX_)
        if (*iter == *out)
            return iter;
    additionsX_.push_back(out);
    return out;    
}

LazyValue* LazyManager::add_multiplication( LazyValue* a , LazyValue *b)
{
            
    LazyValue* check = check_multiplication(a,b);
    if (check)
        return check;
    
    LazyMultiplication* out = new LazyMultiplication(a,b);
    LazyOperator2* tmp = (LazyOperator2*) out;
    if ( multiplications_.look_for (&tmp) )
    {
//         std::cout<<"already found multplication"<<std::endl;
        return tmp;
    }
    multiplications_.store(tmp);    
    return tmp;
}

LazyValue* LazyManager::add_multiplicationX( std::list<LazyValue*> v)
{
    // creation of the new object
    LazyMultiplicationX* out = new LazyMultiplicationX(v);
    
    // check if does not already exist
    for (auto& iter : multiplicationsX_)
        if (*iter == *out)
            return iter;
    multiplicationsX_.push_back(out);
    return out;    
}



LazyValue* LazyManager::compact( LazyValue* a)
{      
    if ( is_additionX(a))
    {
        return compact_additionX( (LazyAdditionX*) a);
    }
    
    if ( is_multiplicationX(a))
    {
        return compact_multiplicationX( (LazyMultiplicationX*) a);
    }    
    return a;
}

LazyValue * LazyManager::compact_additionX (LazyAdditionX *a )
{
    LazyValue* cst = zero_;
    std::list<LazyValue*> vec;
    
    for ( auto iter : a->p_)
    {
        LazyValue * tmp = compact(iter);
 
        if ( is_constant(tmp))
        {
            cst = add_addition(cst,tmp);
        }else if (is_additionX(iter))
        {
            LazyAdditionX *v = (LazyAdditionX*) iter;
            for (auto& iter1 : v->p_)
                vec.push_back( compact(iter1));
        }else 
        {
            vec.push_back( compact(tmp));
        }
    }
    if ( !is_zero(cst))
        vec.push_back(cst);
    return add_additionX(vec);
    
}

LazyValue * LazyManager::compact_multiplicationX (LazyMultiplicationX *a )
{
    LazyValue* cst = one_;
    std::list<LazyValue*> vec;
    
    for ( auto iter : a->p_)
    {     
        if ( is_constant(iter))
        {
            cst = add_multiplication(cst,iter);
        }else if (is_multiplicationX(iter))
        {
            LazyMultiplicationX *v = (LazyMultiplicationX*) iter;
            for (auto& iter1 : v->p_)
                vec.push_back( compact(iter1));
        }
        else
            vec.push_back( compact(iter));
    }
    if ( !is_one(cst))
        vec.push_back(cst);
    return add_multiplicationX(vec);
    
//     return a;
}

LazyValue * LazyManager::explose( LazyValue * in)
{
//     // we do nothing
//     return in;
    
    if (is_additionX(in))
    {
        LazyAdditionX* v = (LazyAdditionX*) in;
        LazyValue* m = zero_;
        for (auto& iter : v->p_)
            m = add_addition( m,explose(iter));
        return m;
    }    

    if (is_cosinus(in))
    {
        LazyCosinus* v = (LazyCosinus*) in;
        return add_cosinus( explose(v->a_));
    }
    
    if (is_constant(in))   return in;
    
    if (is_soustraction(in))   return in;

    if (is_input(in))   return in;

    
    if (is_multiplicationX(in))
    {
        LazyMultiplicationX* v = (LazyMultiplicationX*) in;
        LazyValue* m = one_;
        for (auto& iter : v->p_)
            m = add_multiplication( m,explose(iter));
        return m;
    }
    
    if (is_sinus(in))
    {
        LazySinus* v = (LazySinus*) in;
        return add_sinus( explose(v->a_));
    }
            
    std::cerr<<"Error in "<< __FILE__<<" at line : "<< __LINE__<<" the case of value ";
    in->print();
    exit(63);
}

void LazyManager::init_basic_constant()
{             
    constants_.push_back(zero_);
    constants_.push_back(one_);
    constants_.push_back(minus_one_);        
}

bool LazyManager::is_additionX(LazyValue* in) const
{
    return (in->type_ == LAZYADDITIONX);
//     for (auto& iter : additionsX_)
//         if (iter == in)
//             return true;
//     return false;    
}

bool LazyManager::is_constant( LazyValue* in) const
{
    return (in->type_ == LAZYCONSTANT);
//     for (auto& iter : constants_)
//         if (iter == in)
//             return true;
//     return false;    
}

bool LazyManager::is_cosinus( LazyValue* in) const
{
    return (in->type_ == LAZYCOSINUS);
//     for (auto& iter : cosinus_)
//         if (iter == in)
//             return true;
//     return false;    
}

bool LazyManager::is_multiplicationX(LazyValue* in) const
{
    return (in->type_ == LAZYMULTIPLICATIONX);
//     for (auto& iter : multiplicationsX_)
//         if (iter == in)
//             return true;
// 
//     return false;    
}

bool LazyManager::is_sinus( LazyValue* in) const
{
    return (in->type_ == LAZYSINUS);
//     for (auto& iter : sinus_)
//         if (iter == in)
//             return true;
//     return false;    
}

bool LazyManager::is_soustraction( LazyValue* in) const
{
    return (in->type_ == LAZYSOUSTRACTION);
//     for (auto& iter : soustractions_)
//         if (iter == in)
//             return true;
//     return false;    
}
