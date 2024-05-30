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
    sub_outputs_.clear();
};

Dependance::Dependance(uint index)
{
    index_output_ = index;
    nb_sub_output_ = 0;
    sub_outputs_.clear();
};

void Dependance::add_suboutput( LazyCreator * in, uint nb)
{
    sub_outputs_[nb] = in;
}

void Dependance::compute_dependances()
{
    uint cpt = 0;
    uint counter = 0;
    std::vector< LazyCreator* > vec;
    for (auto out : sub_outputs_)
    {
        out.second->update_list(vec,index_output_);   
        dependances_[cpt++] = vec;
        counter += vec.size();
    }
}

void Dependance::print()
{
    for (auto idep : sub_outputs_)
    {
        std::cout<<"output : "<< idep.second->get_equation()<<std::endl;
    }        
}

inline double Dependance::update( uint cpt )
{        
    std::vector<LazyCreator*>& suboutput = dependances_[cpt];
    for (auto i : suboutput)
    {
        i->compute();
    }
    return sub_outputs_[cpt]->get_value();
}


LazyManager::LazyManager()
{
    one_ = add_parser(new LazyConstant(1.0));
    zero_ = add_parser(new LazyConstant(0));
    
    cone_ = add_creator(one_->explose());
    czero_ = add_creator(zero_->explose());
//     minus_one_ = new LazyConstant(-1.0);
//     init_basic_constant();
}

LazyParser* LazyManager::add_additionX( LazyParser* a , LazyParser *b)
{
//     if(a->is_zero())
//     {
//         return add_parser(b);
//     }
//     if(b->is_zero())
//     {
//         return add_parser(a);
//     }
    
    std::list<LazyParser*> vec;
    vec.push_back(a);
    vec.push_back(b);
    return add_parser(new LazyAdditionX(vec));
}

LazyParser* LazyManager::add_additionX( LazyParser* a , double value)
{
    return add_parser(new LazyAdditionX(value,a));    
}

LazyCreator* LazyManager::add_constant( double a)
{
    return add_creator(new LazyConstant(a));
}

LazyParser* LazyManager::add_constant_parser( double a)
{
    return add_parser(new LazyAdditionX(a));
}

LazyParser* LazyManager::add_cosinus( LazyParser* a)
{
    return add_parser(new LazyCosinus(a));
}

LazyCreator* LazyManager::add_creator( LazyCreator* in)
{
    auto result = creators_.insert(in);
    if (result.second) 
    {
        // L'élément a été inséré, renvoie l'élément inséré
        return *result.first;
    } else {
        // L'élément existe déjà, renvoie l'élément existant
//         
        // FIXME on ne peut pas supprimer car cela supprime aussi le LazyParser en cas de LazyParserCreator
            switch (in->typec_)
            {
                case(LAZYC_ADDITION):
                case(LAZYC_SOUSTRACTION):
                case(LAZYC_MULTIPLICATION):
                    delete in;
                default:
                    break;
            }
//         delete in; // Tu peux supprimer le pointeur que tu as créé car il n'est pas nécessaire
        
        return *result.first;
    }        
}

LazyParser* LazyManager::add_input( const double &a, const std::string& name)
{
    LazyInput* in = new LazyInput(a,name);
    auto result = inputs_.insert(in);
    if (result.second) 
    {
        // L'élément a été inséré, renvoie l'élément inséré
        return *result.first;
    } else {
        // L'élément existe déjà, renvoie l'élément existant
            switch (in->typec_)
            {
                case(LAZYP_ADDITIONX):
                case(LAZYP_MULTIPLICATIONX):
                    delete in;
                default:
                    break;
            }

//         delete in; // Tu peux supprimer le pointeur que tu as créé car il n'est pas nécessaire
        return *result.first;
    }      
}

LazyParser* LazyManager::add_multiplicationX( LazyParser* a , LazyParser *b)
{
//     if(is_zero(a) || is_zero(b))
//         return zero_;
//     
//     if(is_one(a))
//         return add_parser(b);
//     if(is_one(b))
//         return add_parser(a);        
        
    std::list<LazyParser*> vec;
    vec.push_back(a);
    vec.push_back(b);
    return add_parser(new LazyMultiplicationX(vec));
}

LazyParser* LazyManager::add_parser( LazyParser* in)
{
//     if (in->is_zero())  return zero_;
    
    auto result = parsers_.insert(in);
    if (result.second) 
    {
        // L'élément a été inséré, renvoie l'élément inséré
        return *result.first;
    } else {
        // L'élément existe déjà, renvoie l'élément existant
        delete in; // Tu peux supprimer le pointeur que tu as créé car il n'est pas nécessaire
        return *result.first;
    }        
}

LazyCreator* LazyManager::add_output( LazyParser* in, uint index, uint rank )
{
    if (index == 0 && rank == 0)   
    {
        std::cout<<"add output : "<< *in <<std::endl;
        in->print();
    }
    if (outputs_.find(index) == outputs_.end())
    { // there is no such element, we create it
        outputs_[index] = Dependance(index);    
    }   
    LazyCreator *create = in->explose();
    if (index == 0 && rank == 0)
    {
        std::cout<<"add output : "<< *create <<std::endl;
        create->print_tree();
    }
    outputs_[index].add_suboutput(create,rank);
    return create;
}

LazyParser* LazyManager::add_sinus( LazyParser* a)
{
    return add_parser(new LazySinus(a));
}


LazyCreator* LazyManager::add_soustraction( LazyCreator* a , LazyCreator *b)
{
    return  add_creator(new LazySoustraction(a,b));
}

// uint LazyManager::affect()
// {
//     affect_ = true;
//     return counter_;
// }

// LazyValue* LazyManager::check_addition( LazyValue*a , LazyValue*b)
// {            
//     if ( is_zero(a))
//         return b;
//     
//     if ( is_zero(b))
//         return a;
// 
// //     if (is_minus_one(a))
// //     {
// //         return add_soustraction(b,a);
// //     }
// // 
// //     if (is_minus_one(b))
// //     {
// //         return add_soustraction(a,b);
// //     }      
//     return 0;
// }


// LazyValue* LazyManager::check_multiplication( LazyValue*a , LazyValue*b)
// {        
//     if ( is_zero(a) || is_zero(b))
//         return zero_;
//     
//     if ( is_one(a))
//         return b;
//     
//     if ( is_one(b))
//         return a;
//     
//     if (is_constant(a) && is_constant(b))
//     {
//         return add_constant( a->value_*b->value_);
//     }    
//     
//     if (is_constant(a) || is_constant(b))
//     {
// //         LazyAdditionX* out;
// //         if (is_constant(a))
// //         {
// //             out = new LazyAdditionX(a->value_,b);
// //         }
// //         
// //         if (is_constant(b))
// //         {
// //             out = new LazyAdditionX(b->value_,a);
// //         }
// //     
// //         if (out->p_.size() == 0.0)
// //         {
// //             delete out;
// //             return zero_;
// //         }
// // 
// //         auto result = additionsX_.insert( out);
// //         if (result.second) 
// //         {
// //             // L'élément a été inséré, renvoie l'élément inséré
// //             return *result.first;
// //         } else {
// //             // L'élément existe déjà, renvoie l'élément existant
// //             delete out; // Tu peux supprimer le pointeur que tu as créé car il n'est pas nécessaire
// //             return *result.first;
// //         }    
//     }
//     
//     return 0;
// }

uint LazyManager::get_nb_inputs() const
{
    return inputs_.size();
}

LazyParser* LazyManager::get_one() const
{
    return one_;
}

LazyParser* LazyManager::get_zero() const
{
    return zero_;
}
/*
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
*/
bool LazyManager::is_one(LazyParser * in) const
{
    return in == one_;
}

bool LazyManager::is_zero(LazyParser* in) const
{
    return in == zero_;
}

void LazyManager::prepare(  const std::string& name,
                            bool reuse_if_exist)
{
    for (auto& iter : outputs_)
    {
        iter.second.compute_dependances();
    }
    
    if (name == "")
    {
        class_name_ = get_unique_name();  
    }else
    {
        class_name_ = "LazyCppGenerated_" + name;        
        for (char& c : class_name_) {
            if (c == '.') {
                c = '_';
            }
        }                
    }
    
    std::string filename = class_name_ + ".cpp";  
    bool create = true;
    if (reuse_if_exist)
    {
        std::ifstream file(filename);
        if(file.good())
        {
            create = false;
            std::cout<<"We do not need to recreate the file we use the existing one"<<std::endl;
        }        
    }

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
    
    if (create)
    {
        std::ofstream f (filename );
        f<<"#include <vector>\n#include <math.h>\n#include <iostream>\n#include \"LazyGeneratedCode.hpp\" \n\n\n";
        f<<"class "<<class_name_<<": public LazyGeneratedCode\n{\npublic:\n";
        f<<"\t void print_time()\n\t{ \n \t\t std::cout<<\" time of compilation : "<< time(0)<<" \"<<std::endl;\n\t}\n\n";
        f<<"\tunsigned int get_nb_in()const \n\t{\n\t\treturn "<< get_nb_inputs() <<";\n\t}\n\n";
        f<<"\t // intermediate variables\n";

        f<<"\t"<<RealName<<" t["<<nb_in<<"];\n";        
        f<<"\t"<<RealName<<" x["<<LazyCounter<<"];\n";      
        
        f<<"\n\n\tvoid set_input(std::vector<"<< RealName<<"> & in)\n\t{\n";
        for (auto & iter : inputs_)
        {
                f<< "\t\tx["<< iter->id_ <<"] =  in["<<iter->id_ <<"];\n";
        }
        f<<"\t}\n\n";
        
        f<<"\n\n\tvoid set_input(uint index, "<< RealName<<" value)\n\t{\n";
                f<< "\t\tx[index] =  value;"<<std::endl;
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
                for(auto & it3 : it2.second)  
                {
                    if (it3->update_)
                    {
                        f<< "\t\t\t\t\t"<<   it3->file_print("x")  <<"// TYPE"<< it3->typec_<<" eq:"<< it3->get_equation() <<"\n";
                        it3->update_ = false;
                    }
                }
                if (iter.second.sub_outputs_[ it2.first]->id_ == -1)
                    f<<"\t\t\t\t\treturn 0.0;\n" <<std::endl;
                else
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
        std::string command = "g++ -O3 -DNDEBUG -fPIC -shared " + filename /*+ std::string( COMPILE_FLAGS) */+ " -I"  + " " + std::string( INCLUDE_DIR) + " -o lib"+class_name_+".so ";
        std::cout<<"Compilation command is : "<< command<<std::endl;
        int dummy = system ( command.c_str() );
        double compilation_time = get_cpu_time() - tsart;
        std::cout<<"LazyCPP compilation time = "<< compilation_time  <<std::endl;
    }
    
    std::string lib = "./lib"+class_name_ +".so";

    unsigned int count = 0;
    do{
        count++;
        handle_lib_ =dlopen(lib.c_str(), RTLD_LAZY);
        if (!handle_lib_) {
            std::cerr <<"Error1 in "<<__FILE__<<" at line "<<__LINE__<< " : Cannot load library ("<< lib <<"), with the error : " << dlerror() << '\n';
            if(count>10)
            {
                std::cerr<<"Cannot load the library, stopping program"<<std::endl;
                std::cerr<<"Sometimes the following line solve the issue : \n export LD_LIBRARY_PATH=."<<std::endl;
                exit(0);
            }
            sleep(1);
        }        
    }while(!handle_lib_);
    // load the symbols
    count = 0;
    do{
        count++;
        creator_ = (create_code*) dlsym(handle_lib_, "create");
        destructor_ = (destroy_code*) dlsym(handle_lib_, "destroy");
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
    parsers_.clear();
    creators_.clear();
    outputs_.clear();
    clean_files();
}

void LazyManager::update_input()
{
    std::vector<double> inputs(inputs_.size());
    for (auto & iter : inputs_)
        inputs[iter->id_] = iter->value_;
    
    lazycode_->set_input(inputs);    
}

void LazyManager::update_input(uint index, double value)
{
    lazycode_->set_input(index,value);    
}

double LazyManager::update(uint index, uint cpt) const
{
    return lazycode_->function(index,cpt);
}

/////////////////////////////////////////////////////
////////////////////Private functions ///////////////
/////////////////////////////////////////////////////

LazyCreator* LazyManager::add_addition( LazyCreator* a , LazyCreator *b)
{   
//     if (a == czero_) return b;
//     if (b == czero_) return a;
    return add_creator( new LazyAddition(a,b));
}

LazyCreator* LazyManager::add_multiplication( LazyCreator* a , LazyCreator *b)
{   
//     if (a == czero_ || b == czero_) return czero_;
//     if (a == cone_) return b;
//     if (b == cone_) return a;
    return add_creator( new LazyMultiplication(a,b));
}


void LazyManager::clean_files()
{
    if (lazycode_)  
    {
        dlclose( handle_lib_);
//         lazycode_->delete_files();
        destroy_code(lazycode_);        
    }
    lazycode_ = nullptr;
    
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
