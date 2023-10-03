#include <vector>
#include <math.h>
#include <unistd.h>    

typedef double Real;
const std::string RealName = "double";

class LazyGeneratedCode
{
public:
    
    virtual ~LazyGeneratedCode()
    {
//         delete_files();
    }
    
	virtual unsigned int get_nb_in()const  = 0;

	virtual void set_input(std::vector<Real> & in) = 0;

	virtual Real function(unsigned int index, unsigned int out=0) = 0;
    
    virtual void print_all() = 0;
    
    virtual void print_time() = 0;
    
    void delete_files()
    {
        std::string filename = class_name_ + ".cpp";  
        std::string libname = "lib" + class_name_ + ".so";  
        std::string cmd = "rm " + filename + " " + libname;
        int dummy = system(cmd.c_str());
        sleep(1);
    }
    
    void set_class_name( std::string name)
    {
        class_name_ = name;
    }
    
    std::string class_name_;
    
};
// the types of the class factories
typedef LazyGeneratedCode* create_code();
typedef void destroy_code(LazyGeneratedCode*);
