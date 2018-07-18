/*红黑树算法实现
 * 基本动态算法：中序，前序，后序输出
 * 插入，删除*/
#ifndef RB_TREE_H
#define RB_TREE_H
#include <string>
#include <vector>

using namespace std;
const int BLACK = 1;
const int RED = 0;

template <typename dtype>
struct node{
  node* p;
  node* left;
  node* right;
  int color;
  dtype k;
  node(dtype key,int c):p(nullptr),left(nullptr),right(nullptr),k(key),color(c){}
};

template <typename dtype> 
class RBtree{
  public:
    RBtree():root_(NIL_){}
    RBtree(vector<dtype>);
    void insert_node(dtype);
    void delete_node(node<dtype>*);
    void print_pre(); 
    void print_mid();
    void print_aft();
    node<dtype>* get_item(dtype);
  private:
    node<dtype> *const NIL_ = new node<dtype>(0,BLACK);
    void left_rotate(node<dtype>*);
    void right_rotate(node<dtype>*);
    void Updatetree(node<dtype>*);
    void fix_up(node<dtype>*);
    node<dtype>* find_min(node<dtype>*);
    void up(node<dtype>*,node<dtype>*);
    node<dtype>* root_;
};
#endif
