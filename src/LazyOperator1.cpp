// #include "LazyOperator1.hpp"
// 
// void LazyOperator1::compact()
// {
//     if (!compacted_)
//     {
//         compacted_ = true;
//         a_->compact();
//     }
// }
// 
// LazyValue* LazyOperator1::explose()
// {
//     if (!explosed_)
//     {
//         explosed_ = true;
//         a_ = a_->explose();
//     }
//     return this;
// }
// 
// void LazyOperator1::update_list(std::vector<LazyValue*>& vec, int current)
// {
// //     std::cout<<"\t update_list of "<<std::endl;
// //     print_equation();
// //     std::cout<<"update_ = " << update_ <<std::endl;
// //     std::cout<<"current = " << current <<std::endl;
//     if (update_ < current)
//     {
// //         std::cout<<"update sons"<<std::endl;
//         a_->update_list(vec,current);
//         vec.push_back(this);            
//     }
//     update_ = current;
// //     std::cout<<"\t end update_list of "<<std::endl;
// //     print_equation();    
// }   
// 
// 
// void LazyOperator1::propag_update(int v)
// {
//     if (update_ < v)
//     {
//         update_ = v;
//         a_->propag_update(v);
//     }    
// }
//    
// bool LazyOperator1::operator == (const LazyOperator1& A) const
// {
//     return (a_ == A.a_ );
// }
//     
