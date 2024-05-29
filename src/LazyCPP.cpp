#include "LazyCPP.hpp"

LazyManager LMANAGER;


void LazyAddOutput(LazyVariable& in,uint index,uint rank)
{
    in.creator_ = LMANAGER.add_output(in.parser_, index,rank);
}

uint LazyGetNbInputs()
{
    return LMANAGER.get_nb_inputs();
}

void LazyCleanFiles()
{
    LMANAGER.clean_files();
}

void LazyPrepare(const std::string& filename,
                 bool reuse_if_exist)
{
    LMANAGER.prepare(filename, reuse_if_exist);
}

// void LazyPrintAll()
// {
//     LMANAGER.print_all();
// }
// 
// void LazyPrintAllInputs()
// {
//     LMANAGER.print_all_inputs();
// }
// 
// void LazyPrintAllOutputs()
// {
//     LMANAGER.print_all_output_equations();
// }

void LazyReset()
{
    LMANAGER.reset();
}

void LazyUpdateInput()
{
    LMANAGER.update_input();
}

void LazyUpdateInput(uint index, double value)
{
    LMANAGER.update_input(index,value);
}

double LazyUpdateOutput(uint index, uint cpt)
{
    return LMANAGER.update(index,cpt);
}

