#include "LazyOperatorX.hpp"

 

// void LazyOperatorX::propag_update(int v)
// {
//     update_ = v;
//     for (auto iter : p_)
//     {
//         iter->propag_update(v);
// //         update_ = update_ || iter->update_;
//     }
// }


// void LazyOperator2::propag_update(int v)
// {
//     if (update_ < v)
//     {
//         update_ = v;
//         a_->propag_update(v);
//         b_->propag_update(v);
//     }    
// //     update_ = a_->update_ || b_->update_;
// }
//    


// void LazyOperatorX::update_list(std::vector<LazyValue*>& vec, int current)
// {
//     std::cerr<<"FILE : "<< __FILE__<<" line : "<< __LINE__<<std::endl;
//     std::cerr<<"THIS FONCTION SHOULD NOT BE CALLED"<<std::endl;
//     std::exit(1234);
//     
// //     if (update_ < current)
// //     {
// //         update_ = current;
// //         for (auto iter : p_)
// //         {
// //             update_list(vec,update_);
// //         }
// //     }    
// }   

       
// bool LazyOperatorX::operator == (const LazyOperatorX& A) const
// {
//     if (p_.size() != A.p_.size())
//         return false;
//        
//     return p_ == A.p_;
// }

