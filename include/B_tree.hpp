/*本代码用来实现，算法导论中B-tree相关功能*/

#include <vector>
#include <tuple>
#include <iostream>
using namespace std;


//树结点实现
template <typename dtype>
struct tree_node{
    int num_;//结点所含关键字的个数
    vector<dtype> keys_;//所包含的关键字
    bool leaf_;//该节点是否是子树
    vector<tree_node*> next_;//指向子树的指针
    tree_node():num_(0),leaf_(true){}
};
//DISK_WRITE
template <typename dtype>
void DISK_WRITE(tree_node<dtype>* x){
    for(int i=0;i<x->num_;i++){
        cout<<"keys"<<x->keys_[i]<<" ";
    }
    cout<<endl;
}
template <typename dtype>
class B_tree{
    public:
	B_tree():t_(2){root_ = new tree_node<dtype>();}
	B_tree(int a):t_(a){root_ = new tree_node<dtype>();}
        pair<tree_node<dtype>* ,int> search(tree_node<dtype>* ,dtype );
        void insert_(dtype key); 
	void split_child(tree_node<dtype>* ,int);
	void delete_(tree_node<dtype>* T,dtype key);
	tree_node<dtype>* root_;
	void merge(tree_node<dtype>*,int);
	void delete_final(dtype key);
	int t_;

};


