#include "RBtree.h"
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;


template<typename dtype>
void RBtree<dtype>::insert_node(dtype x){
    //insert the node in to
    node<dtype>* inNode = new node<dtype>(x,BLACK); 
    inNode->left = NIL_;
    inNode->right = NIL_;
    inNode->p = NIL_;
    if(root_==NIL_)root_ = inNode;
    else{
        node<dtype>* p = root_;
        node<dtype>* par = NIL_;
        dtype tem = p->k;
        while(p!=NIL_){
            par = p;
            tem = p->k;
            if(x >= tem)p = p->right;
            else p = p->left;
        }
        inNode->p = par;
        inNode->color = RED;
        if(x>=tem){
            par->right = inNode;
        }else{
            par->left = inNode;
        }
    Updatetree(inNode);    
    }
}

template<typename dtype>
void RBtree<dtype>::Updatetree(node<dtype>* z){
    while(z->p->color==RED){
        if(z->p->p->left == z->p){
            //如果z的父节点为左子树
            //case1 ,叔父结点为红色
            if(z->p->p->right->color == RED){
                z->p->color = BLACK;
                z = z->p->p;
                z->color = RED;
                z->right->color = BLACK;
            }else{
                //case 2
                if(z->p->right==z){
                    z = z->p;
                    left_rotate(z);
                }
                //case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(z->p->p);break;
            }
        }else{
            if(z->p->p->left->color == RED){
                z->p->color = BLACK;
                z = z->p->p;
                z->color = RED;
                z->left->color = BLACK;
            }else{
                //case 2
                if(z->p->left==z){
                    z = z->p;
                    right_rotate(z);
                }
                //case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(z->p->p);
                break;
            }
        }
    }
    root_->color = BLACK;
}
template<typename dtype>
void RBtree<dtype>::right_rotate(node<dtype>* z){
    node<dtype>* l = z->left;
    z->left = l->right;
    l->right->p = z;
    l->p = z->p;
    if(z==z->p->left){
        z->p->left = l;
    }else if(z==z->p->right){
        z->p->right = l;
    }
    z->p = l;
    l->right = z;
    if(root_==z)root_=l;
}

template<typename dtype>
void RBtree<dtype>::left_rotate(node<dtype>* z){
    node<dtype>* r = z->right;
    z->right = r->left;
    r->left->p = z;
    r->p = z->p;
    if(z==z->p->left){
        z->p->left = r;
    }else if(z==z->p->right){
        z->p->right = r;
    }
    z->p = r;
    r->left = z;
    //这个时候会有问题，即当z为root的时候，这个时候，root需要改成r
    if(z==root_)root_=r;
}

template<typename dtype>
void RBtree<dtype>::print_pre()
{
    stack<node<dtype>* > s; 
    node<dtype>* p = root_;
    while(!s.empty()||p!=NIL_){
        while(p!=NIL_){
             cout<<p->k<<" ";
             s.push(p);
             p = p->left;
        }
        if(!s.empty()){
             p = s.top();
             s.pop();
             p = p->right;
        }
    }
}

template<typename dtype>
void RBtree<dtype>::print_mid()
{
    stack<node<dtype>* > s; 
    node<dtype>* p = root_;
    while(!s.empty()||p!=NIL_){
        while(p!=NIL_){
             s.push(p);
             p = p->left;
        }
        if(!s.empty()){
             p = s.top();
             cout<<p->k<<" ";
             s.pop();
             p = p->right;
        }
    }
}
template<typename dtype>
void RBtree<dtype>::print_aft()
{
     stack<node<dtype>* >s;
     unordered_map<node<dtype>*,int> flag;
     node<dtype>* p = root_;
     while(!s.empty()||p!=NIL_){
         while(p!=NIL_){
             s.push(p);
             p = p->left;
         }
         if(!s.empty()){
             p = s.top();
             if(p->right!=NIL_&&!flag[p]){
                 flag[p] = 1;
                 p = p->right;
             }else{
                 cout<<p->k<<" ";
                 s.pop();
                 p = NIL_;
             }
         }
     }
}

/*
    该函数的目的是，将p的父节点指向q，如果p为根结点，那么q为根结点
*/
template<typename dtype>
void RBtree<dtype>::up(node<dtype>* p,node<dtype>* q){
    q->p = p->p;
    if(p==root_){root_=q;}
    else if(p->p->left==p){
        p->p->left = q;
    }else{
        p->p->right = q;
    }
}
template<typename dtype>
node<dtype>* RBtree<dtype>::find_min(node<dtype>* x){
    while(x->left!=NIL_){
        x = x->left;
    }    
    return x;
}
template<typename dtype>
void RBtree<dtype>::delete_node(node<dtype>* z)
{
    /*观察z有没有左子树或者右子树*/
    node<int>* y;
    node<int>* x;
    y = z;
    int original_color = z->color;
    if(z->left==NIL_){
        x = z->right;
        up(z,z->right);
    }else if(z->right==NIL_){
        x = z->left;
        up(z,z->left);
    }else{
        y = find_min(z->right);
        x = y->right;
        if(y!=z->right){
            //当y是z的右子树的时候，直接将yup到z上即可不需要管右子树。
            //但是如果不是的话，需要将其右子树也放到y上
            up(y,x);
            y->right = z->right;
            y->right->p = y;
        }
        original_color = y->color;
        up(z,y);
        y->p = z->p;
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    delete z;
    if(original_color == BLACK) fix_up(x);
}
/*
fix_up分为四种情况，处理的问题实际上都是x->p结点的子树黑色结点个数不一致，
原因在于原本的x->p为黑色，删除掉这个结点之后，个数少了一个。
这个时候如果x的颜色是红的，那么直接编程黑即可，如果x是root那么x直接变成黑色即可。
否则分为4中情况：
1.如果x的叔父结点w为黑色，并且w的右子树为红色，那么这个时候，对x的父节点进行左旋操作
，在改变下颜色，即可满足要求了。这里的原因在于这个时候可以给一个黑色到左边。
2.如果w为黑色，其右子树为黑色，左子树为红色这个时候，首先对w右旋，改变颜色，即可得到
情况1.
3.如果w为黑色，右子树为黑色，左子树为黑色，这个时候，直接令w为红色，然后x指向父节点，
再进行考虑
4.如果w为红色，则x父节点一定是黑色，这个时候在父节点改变颜色，左旋，然后w指向新的x的
叔父结点。
*/
template<typename dtype>
void RBtree<dtype>::fix_up(node<dtype>* x){
    node<dtype>* w;
    while(x->color!=RED&&x!=root_){
        if(x==x->p->left){
        //x为左子树的时候，右子树的情况反过来
            w = x->p->right;
            if(w->color==RED){
            //情况4
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(x->p);
                w = x->p->right;
            }else{
                //w的颜色为黑色
                if(w->left->color==BLACK&&w->right->color==BLACK){
                //情况3
                    w->color = RED;
                    x = x->p;
                }else{
                    if(w->left->color == RED&&w->right->color==BLACK){
                        //情况2
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = w->p;
                    }
                    //情况1
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->p);
                    x = root_;//退出循环，并且还能保证root_为黑色。
                }
            }
        }
        else{
        //x为右子树的情况    
            w = x->p->left;
            if(w->color==RED){
            //情况4
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(x->p);
                w = x->p->left;
            }else{
                //w的颜色为黑色
                if(w->right->color==BLACK&&w->left->color==BLACK){
                //情况3
                    w->color = RED;
                    x = x->p;
                }else{
                    if(w->right->color == RED&&w->left->color==BLACK){
                        //情况2
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = w->p;
                    }
                    //情况1
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->p);
                    x = root_;//退出循环，并且还能保证root_为黑色。
                }
            }
        }
    }
    x->color = BLACK;
}
template<typename dtype>
node<dtype>* RBtree<dtype>::get_item(dtype x)
{
    node<dtype> *p = root_;
    while(p!=NIL_){
        if(p->k==x)return p;
        if(x<p->k)p=p->left;
        else p = p->right;
    }
    return nullptr;
}
int main()
{
    RBtree<int> tree;
    vector<int> num{4,6,8,3,5,2};
    for(auto i:num){
        tree.insert_node(i);
    }
    tree.print_pre();
    cout<<endl;
    tree.print_mid(); 
    cout<<endl;
    tree.print_aft();
    cout<<endl;
    node<int>* p =tree.get_item(5);
    tree.delete_node(p);
    tree.print_pre();
}

