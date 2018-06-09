/*
 * 这个数据结构对应的是
 * 不相交集合的实现：
 * 它针对的是这样的一种情况：
 * 1.在实现最小生成树的过程中，遇到了这样一个设计的困难，我需要
 * 让每一个元素，如果两个元素在一个集合，那么它们返回的集合就是一样的。（因为不集合之间不相交，
 * 所以给定一个元素，它就要返回这个元素属于的集合），之前的思路一直都是，对每一个元素都建立一个集合，
 * 然后在后面的操作中，更新这个元素的集合，这样的缺点在于，这就需要每进行一次操作，都要将所有元素的集合
 * 进行更新。本质在于这里，各个元素之间的集合不能同步的进行更新。
 * 而现在这个不相交集合，是以集合为单位，每一个集合用同一个标识符来确定，每一个元素，可以用find_set函数，就
 * 可以返回其集合标识。还要定义集合的union运算，来融合两个集合。*/
#ifndef DIS_JOINT_H
#define DIS_JOINT_H
#include <iostream>
using namespace std;
template<typename dtype>
struct list_data;
template<typename dtype>
struct mySet{
    list_data<dtype>* first;
    list_data<dtype>* tail;
    int num;
    mySet<dtype>():first(nullptr),tail(nullptr),num(0){} 
};
template<typename dtype>
struct list_data{
    dtype data;
    mySet<dtype> *head;
    list_data<dtype> *next;
    list_data<dtype>(dtype a,mySet<dtype>* b):data(a),head(b),next(nullptr){}
};

template<typename dtype>
class dis_set{
    public:
	    dis_set(dtype* data,int n);
	    list_data<dtype>* find(dtype );
	    mySet<dtype>* set_;
};

//这里一开始的函数，写成了，输入为数据对象而不是指针，这样就会存在问题
//因为我函数体中，要用到该数据对象的指针，而如果输入的是对象的话，就会造成
//此时数据对象的指针是，函数中局部变量的指针和原本的数据指针是不一样的。就会导致
//结果不一致。
template<typename dtype>
void SetUnion(dis_set<dtype>* a,dis_set<dtype>* b){
    if(b->set_->num>a->set_->num){
    b->set_->num += a->set_->num;
    list_data<dtype>* p = b->set_->tail;
    b->set_->tail = a->set_->tail;
    p->next = a->set_->first;
    p = p->next;
    while(p!=nullptr){
        p->head = b->set_;
        p = p->next;
    }
    a->set_ = b->set_;
    }else{
    a->set_->num += b->set_->num;
    list_data<dtype>* p = a->set_->tail;
    a->set_->tail = b->set_->tail;
    p->next = b->set_->first;
    p = p->next;
    while(p!=nullptr){
        p->head = a->set_;
        p = p->next;
    }
    b->set_ = a->set_;
    }
}
void print_set(dis_set<int>);
template class dis_set<int>;



#endif
