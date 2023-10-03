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
        out.second->update_list(vec,index_output_);
        dependances_[cpt++] = vec;
        counter += vec.size();
    }
}

// void Dependance::re_init_known()
// {
//     uint cpt = 0;
//     uint counter = 0;
//     std::vector< LazyValue* > vec;
//     for (auto out : sub_outputs_)
//     {
//         out.second->re_init(vec);
//         dependances_[cpt++] = vec;
//         counter += vec.size();
//     }
// }

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
    if (outputs_.find(index) == outputs_.end())
    { // there is no such element, we create it
        outputs_[index] = Dependance(index);    
    }   
    in->compact();
    LazyValue *output = in->explose();

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
    for (auto& iter : soustractions_)
        if (*iter == *out)
            return iter;    
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
    for (auto& iter : outputs_)
    {
        iter.second.compute_dependances();
    }
    std::string class_name_ = get_unique_name();  
    std::string filename = class_name_ + ".cpp";  
    std::ofstream f (filename );
    f<<"#include <vector>\n#include <math.h>\n#include <iostream>\n#include \"LazyGeneratedCode.hpp\" \n\n\n";
    f<<"class "<<class_name_<<": public LazyGeneratedCode\n{\npublic:\n";
    f<<"\t void print_time()\n\t{ \n \t\t std::cout<<\" time of compilation : "<< time(0)<<" \"<<std::endl;\n\t}\n\n";
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
//             else
//             {
//                 f<< "\t\t\t\t\t//"<<   it3->file_print("x")  <<";\n";
//                 it3->update_ = false;                
//             }
            
            f<<"\t\t\t\t\treturn x["+ std::to_string(iter.second.sub_outputs_[ it2.first]->id_) +"];\n" <<std::endl;
        }
        f<<"\t\t\t\t\tdefault: return 0.;\n\t\t\t\t};\n";
        f<<"\t\t\t\tbreak;\n";          
        
    }    
    f<<"\t\t\tdefault: return 0.;\n";
    f<<"\n\t\t}\n\t}";
    
    f<<"\n\nvoid print_all()\n{\n";
    f<<"\tfor (int i=0;i<"<< LazyCounter<<";i++)\n"; 
    f<<"\t\tprintf(\"x[%d] = %f   \\n\",i,x[i]);\n"; 
    f<<"}\n\n";
    f<<"\n};\n\n";
       
    
    f<<"extern \"C\" " + class_name_ +"* create()\n{\n\treturn new " + class_name_ + "();\n}\n\n";
    f<<"extern \"C\" void destroy(" + class_name_ +"* p)\n{\n\tdelete p;\n}\n\n";

    f.close();   
    
    double tsart  = get_cpu_time();
    // Create the library
    std::string command = "g++ -O3 -ggdb -shared " + filename + std::string( COMPILE_FLAGS) + " -I"  + " " + std::string( INCLUDE_DIR) + " -o lib"+class_name_+".so -fPIC";
    int dummy = system ( command.c_str() );
    double compilation_time = get_cpu_time() - tsart;
       
    std::string lib = "./lib"+class_name_ +".so";

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
    lazycode_->set_class_name(class_name_);
}

void LazyManager::print_all() const
{
    lazycode_->print_all();
}

void LazyManager::print_all_inputs() const
{
    for (auto& iter : inputs_)
    {
        std::cout<<" input : "<< iter->name_<<" : "<< iter->value_<<std::endl;
    }
}

void LazyManager::print_all_output_equations()
{
    for (auto& iter : outputs_)
    {
        iter.second.print();
    }
}

void LazyManager::reset()
{
    inputs_.clear();
    additionsX_.clear();
    additions_.clear();
    cosinus_.clear();
    multiplications_.clear();
    multiplicationsX_.clear();
    sinus_.clear();
    soustractions_.clear();
    constants_.clear();
    init_basic_constant();
    counter_ = 0;
    affect_ = true;
    
    if (lazycode_)  
    {
        lazycode_->delete_files();
        destroy_code(lazycode_);
    }
    lazycode_ = nullptr;
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
    {
        if (*iter == *out)
            return iter;
    }
    multiplicationsX_.push_back(out);
    return out;    
}

std::string LazyManager::get_unique_name()const
{
    srand(time(NULL));
    std::string out;
    bool found;
    do{
        out = "LazyCPPGenerated_"+ std::to_string(rand());
        std::ifstream infile(out+".cpp");
        found = infile.good();
    }while(found);
    return out;
}

void LazyManager::init_basic_constant()
{             
    constants_.push_back(zero_);
    constants_.push_back(one_);
    constants_.push_back(minus_one_);        
}

bool LazyManager::is_addition(LazyValue* in) const
{
    return (in->type_ == LAZYADDITION);
}

bool LazyManager::is_additionX(LazyValue* in) const
{
    return (in->type_ == LAZYADDITIONX);
}

bool LazyManager::is_constant( LazyValue* in) const
{
    return (in->type_ == LAZYCONSTANT);
}

bool LazyManager::is_cosinus( LazyValue* in) const
{
    return (in->type_ == LAZYCOSINUS);
}

bool LazyManager::is_multiplication(LazyValue* in) const
{
    return (in->type_ == LAZYMULTIPLICATION);
}

bool LazyManager::is_multiplicationX(LazyValue* in) const
{
    return (in->type_ == LAZYMULTIPLICATIONX);
}

bool LazyManager::is_sinus( LazyValue* in) const
{
    return (in->type_ == LAZYSINUS);
}

bool LazyManager::is_soustraction( LazyValue* in) const
{
    return (in->type_ == LAZYSOUSTRACTION);
}
