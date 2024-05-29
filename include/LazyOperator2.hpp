// #ifndef __LAZYOPERATOR2_HPP__
// #define __LAZYOPERATOR2_HPP__
// 
// #include "LazyValue.hpp"
// 
// class LazyOperator2 : public LazyValue {
// public:
//     
//     /// update the list of the dependancies
// //     virtual void add_to_list(std::vector<LazyValue*>& vec);        
//         
// //     virtual void check_known();
//     
//     virtual inline void compute() = 0;
//     
//     virtual void compact();
//     
//     virtual LazyValue* explose();
//     
//     virtual void propag_update(int up =-1);
//     
//     virtual void update_list(std::vector<LazyValue*>& vec, int current);
//     
//     virtual bool operator == (const LazyOperator2& A) const;
// 
//     LazyValue* a_=nullptr;
//     LazyValue* b_=nullptr;
// };
// 
// #endif //  __LAZYADDITION_HPP__
