// #include "LazyOperator2.hpp"
// 
// 
// void LazyOperator2::compact()
// {
//     if (!compacted_)
//     {
//         compacted_ = true;    
//         a_->compact();
//         b_->compact();
//     }
// }
// 
// LazyValue* LazyOperator2::explose()
// {
//     if (!explosed_)
//     {
//         explosed_ = true;
//         a_ = a_->explose();
//         b_ = b_->explose();
//     }
//     return this;
// }
// 
// void LazyOperator2::update_list(std::vector<LazyValue*>& vec, int current)
// {
//     if (update_ < current)
//     {
// //         std::cout<<"update sons"<<std::endl;
//         a_->update_list(vec,current);
//         b_->update_list(vec,current);
//         vec.push_back(this);            
//     }
//     update_ = current;
// }    
// 
// 
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
// bool LazyOperator2::operator == (const LazyOperator2& A) const
// {
//     return (a_ == A.a_ && b_ == A.b_) || (a_ == A.b_ && b_ == A.a_);
// }
// 
