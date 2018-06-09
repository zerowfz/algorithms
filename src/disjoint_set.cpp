#include "disjoint_set.h"
#include <iostream>
using namespace std;

template<typename dtype>
dis_set<dtype>::dis_set(dtype* data,int n){
    set_ = new mySet<dtype>();
    set_->first = new list_data<dtype>(*data,set_);
    list_data<dtype>* p = set_->first;
    set_->num++;
    for(int i=1;i<n;i++){
        p->next = new list_data<dtype>(data[i],set_);
        p = p->next;
        set_->num++;
    }
    set_->tail = p;
}
template<typename dtype>
list_data<dtype>* dis_set<dtype>::find(dtype data){
    list_data<dtype>* p = set_->first;
    for(int i = 0;i<set_->num;i++){
        if(p->data==data)break;
        p = p->next;
    }
    return p->head->first;
}

void print_set(dis_set<int> s){
    list_data<int>* p = s.set_->first;
    for(int i=0;i<s.set_->num;i++){
        cout<<p->data<<" ";
	p = p->next;
    }	
}
/*
int main()
{
    int a[4]={1,2,3,4};
    int b[2]={5,6};
    dis_set<int> set1(a,4);
    dis_set<int> set2(b,2);
    cout<<set2.set_->first->head<<endl; 
    cout<<&set1.set_<<endl;
    //test find
    cout<<(set1.find(4)==set1.find(3))<<endl;
    //test unioin
    cout<<"adfsf"<<&set2<<endl;
    SetUnion(&set1,&set2);
    list_data<int>* p = set1.set_->first;
    for(int i=0;i<set1.set_->num;i++){
        cout<<p->data<<" "<<p->head<<endl;
	p = p->next;
    }
    cout<<"set2:"<<endl;
    p = set2.set_->first;
    for(int i=0;i<set2.set_->num;i++){
        cout<<p->data<<" "<<p->head<<endl;
	p = p->next;
    }
    cout<<(set1.find(5)==set1.find(2));
}
*/
