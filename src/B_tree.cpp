#include "B_tree.hpp"

template <typename dtype>
pair<tree_node<dtype>*,int> B_tree<dtype>::search(tree_node<dtype>* x,dtype k)
{
    int i = 0;
    while(i<x->num_ && k>x->keys_[i])
	i++;
    if(i<x->num_&&k==x->keys_[i])
	return pair<tree_node<dtype>*,int> {x,i};
    else if (x->leaf_) return pair<tree_node<dtype>*,int>();
    else {
        //DISK_READ(x->next_[i]);
	return search(x->next_[i],k);
    }
}

template <typename dtype>
void B_tree<dtype>::split_child(tree_node<dtype>* x,int i){
    //该函数实现，对x这个结点中的第i个子树，进行划分（这里默认
    //第i个子树key已经满了,所以才进行划分的）
    tree_node<dtype>* z = new tree_node<dtype>();;
    tree_node<dtype>* y = x->next_[i];
    z->leaf_ = y->leaf_;
    z->num_=t_-1;
    for(int j=0;j<t_-1;j++)z->keys_.push_back(y->keys_[j+t_]);
    if (!y->leaf_)for(int j=0;j<t_;j++)z->next_.push_back(y->next_[j+t_]);
    y->num_=t_-1;
    x->next_.insert(x->next_.begin()+i+1,z);
    x->keys_.insert(x->keys_.begin()+i,y->keys_[t_-1]);
    x->num_ +=1;
    DISK_WRITE(y);
    DISK_WRITE(z);
    DISK_WRITE(x);
    //注意这里的num_是有必要的，因为，实际上是根据这个num_来判定vector中那一部分是有效值的。
}
template <typename dtype>
void B_tree<dtype>::insert_(dtype k)
{
    //这里要考虑当根的个数为2t-1的时候，需要产生新的根结点。
    if (root_->num_==2*t_-1){
        tree_node<dtype> *s = new tree_node<dtype>();
	s->leaf_ = false;
	s->next_.push_back(root_);
	split_child(s,0);
	root_=s;
    }
    tree_node<dtype>* tem = root_;
    //下面是一个迭代过程，用循环来写的
    while(!tem->leaf_)
    {
	int i=0;
        for(i=0;i<tem->keys_.size();i++){
	    if(k<tem->keys_[i])break;
	}
	tree_node<dtype>* tem2 = tem->next_[i];
	if(tem2->num_ ==2*t_-1) {
            split_child(tem,i);//如果所在的路径上有满的结点，分裂开
	    if(k>tem->keys_[i])i++;//比较k和新的第i个结点的大小
	}
	tem = tem->next_[i];//此时已经保证了tem是非满的
    }
    int i=0;
    for(i=0;i<tem->keys_.size();i++)
	if(k<tem->keys_[i])break;
    tem->keys_.insert(tem->keys_.begin()+i,k);
    tem->num_++;
    DISK_WRITE(tem);
}
template <typename dtype>
void B_tree<dtype>::delete_(tree_node<dtype>* T,dtype key){
/*输入的x的第i个结点个数此时已经是t-1,我们需要调用该函数，使得其结点个数为t，然后才能进行删除操作。
 两种处理方法：1.如果左右两边相邻结点个数都是大于t-1的那么，可以通过从将父节点key加入到该节点，并用父节点key的前继或者后继作为新的key
 2.如果两边都是t-1，那么将该结点和左边的以及父节点key融合为新的结点。*/
    int i=0;
    tree_node<dtype>* tem;
    for(i=0;i<T->num_;i++){
        if(key == T->keys_[i]){
	    if(T->leaf_){T->keys_.erase(T->keys_.begin()+i);T->num_--;return;}
	    else {
		    //如果是中间结点
		    if(T->next_[i]->num_>=t_){
		        T->keys_[i] = (*(T->next_[i]->keys_.end()-1));
			tem = T->next_[i];
			key = T->keys_[i];
			//delete_(T->next_[i],T->keys_[i]);
		    }else if(T->next_[i+1]->num_>=t_){
		        T->keys_[i] = (*(T->next_[i+1]->keys_.begin()));
			tem = T->next_[i+1];
			key = T->keys_[i];
			//delete_(T->next_[i+1],T->keys_[i]);
		    }else{
			merge(T,i);
			//delete_(T->next_[i],key);
			tem = T->next_[i];
		    }
	    }
	    
	}
	else if(T->leaf_){cout<<"找不到";return ;}
	else if(key<T->keys_[i]){tem = T->next_[i];break;}
    }
    //现在就是看tem是否num_小于t_，如果那么进行一系列操作将，这个值变成t_
    //tree_node<dtype>* tem = T->next_[i];
    tree_node<dtype>* tem2;
    if(tem->num_<t_){
        if(T->next_[i-1]->num_>(t_-1)&&i>0){
	    tem2 = T->next_[i-1];
	    tem->keys_.insert(tem->keys_.begin(),T->keys_[i-1]);
	    if (!tem->leaf_)
	        tem->next_.insert(tem->next_.begin(),*(tem2->next_.end()-1));
	    T->keys_[i-1] = *(tem2->keys_.end()-1);
	    tem2->next_.pop_back();
	    tem2->num_--;
	    tem2->keys_.pop_back();
	}else if(T->next_[i+1]->num_>(t_-1)&&i<T->num_){
	    tem2 = T->next_[i+1];
	    tem->keys_.push_back(T->keys_[i]);
	    if(!tem->leaf_)
		tem->next_.push_back(tem2->next_[0]);
	    T->keys_[i]=tem2->keys_[0];
	    tem2->num_--;
	    tem2->next_.erase(tem2->next_.begin());
	    tem2->keys_.erase(tem2->keys_.begin());
	}else {
            tree_node<dtype>* tem;
	    if(i==T->num_)i--;
	    merge(T,i);
	    tem = T->next_[i];
	}
    }
    delete_(tem,key);
    return;
}
template <typename dtype>
void B_tree<dtype>::merge(tree_node<dtype>* T,int i){
    //融合T->next[i]与T->next[i+1]，去掉了T->keys_[i]
        T->next_[i+1]->keys_.insert(T->next_[i+1]->keys_.begin(),T->keys_[i]);         
	T->next_[i+1]->keys_.insert(T->next_[i+1]->keys_.begin(),\
			T->next_[i]->keys_.begin(),\
			T->next_[i]->keys_.begin()+T->next_[i]->num_);
	if(!T->next_[i]->leaf_)
	T->next_[i+1]->next_.insert(T->next_[i+1]->next_.begin(),\
			T->next_[i]->next_.begin(),\
			T->next_[i]->next_.begin()+T->next_[i]->num_+1);
	T->next_[i+1]->num_ += (T->next_[i]->num_+1);
	T->next_[i] = nullptr;
	T->keys_.erase(T->keys_.begin()+i);
	T->next_.erase(T->next_.begin()+i);
	T->num_ --;
}
template <typename dtype>
void B_tree<dtype>::delete_final(dtype key){
    if (root_->num_==1&&root_->next_[0]->num_<t_&&root_->next_[1]->num_<t_)
    {
        merge(root_,0);
	root_ = root_->next_[0];
	DISK_WRITE(root_);
    }
    delete_(root_,key);
}
template class B_tree<int>;
