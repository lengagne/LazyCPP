#include "LazyCPP.hpp"

LazyManager LMANAGER;


void LazyAddOutput(LazyVariable& in,uint index,uint rank)
{
    in.ref_ = LMANAGER.add_output(in.ref_, index,rank);
}

uint LazyGetNbInputs()
{
    return LMANAGER.get_nb_inputs();
}

void LazyCleanFiles()
{
    LMANAGER.clean_files();
}

void LazyPrepare()
{
    LMANAGER.prepare();
}

void LazyPrintAll()
{
    LMANAGER.print_all();
}

void LazyPrintAllInputs()
{
    LMANAGER.print_all_inputs();
}

void LazyPrintAllOutputs()
{
    LMANAGER.print_all_output_equations();
}

void LazyReset()
{
    LMANAGER.reset();
}

double LazyUpdate(uint index, uint cpt)
{
    return LMANAGER.update(index,cpt);
}

