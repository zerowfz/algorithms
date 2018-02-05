/*红黑树算法实现
 * 基本动态算法：中序，前序，后序输出
 * 插入，删除*/
#ifndef RB_TREE_H
#define RB_TREE_H
#include <string>
#include <vecotr>

template <typename key>
struct node{
  node* p_;
  node* left_;
  node* right_;
  key k_;
};
template <typename key> 
class RBtree{
  public:
    RBtree(){root_ = new node();nil_ = new node();}
    RBtree(vector<key>);
    void output_p();
    void output_m();
    void output_a();
    void insert_node(key);
    void delete_node(key);
  private:
    node* root_;
    node* nil_;
    node* create(key x)
    {
    node* n = new node();
    n->key = x;
    return n;
    }
};
#endif
