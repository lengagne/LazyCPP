#ifndef __LAZYCPP_HPP__
#define __LAZYCPP_HPP__

#include "LazyValue.hpp"
#include "LazyInput.hpp"
#include "LazyConstant.hpp"

#include "LazyAddition.hpp"
#include "LazyMultiplication.hpp"


#include "LazyMultiplicationX.hpp"
#include "LazyAdditionX.hpp"
#include "LazySoustraction.hpp"

#include "LazyCosinus.hpp"
#include "LazySinus.hpp"


// #include "LazyManager.hpp"

#include "LazyVariable.hpp"

class LazyVariable;

// LazyManager LMANAGER;

// LazyManager LMANAGER;

void LazyAddOutput(const LazyVariable& in,uint index,uint rank);
// 
// void LazyGetInfo();
// 
uint LazyGetNbInputs();

void LazyPrepare();
// 
// void LazyPrintGraph(LazyVariable& in);
// 
void LazyPrintAllInputs();
// 
// void LazyPrintOutputGraph(uint index, uint cpt);
// 
void LazyReset();

double LazyUpdate(uint index, uint cpt);

// void LazyUpdateAll();

#endif // __LAZYCPP_H__
