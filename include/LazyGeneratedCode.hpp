#include <vector>
#include <math.h>

typedef double Real;
const std::string RealName = "double";

class LazyGeneratedCode
{
public:
	virtual unsigned int get_nb_in()const  = 0;

	virtual void set_input(std::vector<Real> & in) = 0;

	virtual Real function(unsigned int index, unsigned int out=0) = 0;
    
    virtual void print_time() = 0;
    
    
};
// the types of the class factories
typedef LazyGeneratedCode* create_code();
typedef void destroy_code(LazyGeneratedCode*);
