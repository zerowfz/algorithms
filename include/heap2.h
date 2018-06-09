/*
 * 优先队列的数据结构
 * 默认是用vector来存储数据，这里利用了数组来表示完全二叉树：
 * i对应的子结点为(i+1)*2-1,(i+1)*2。
 *数据从0开始存储。
 *
 * */

#include <vector>
#include <iostream>
using namespace std;

template<typename dtype>
class less_{
  public:
    bool operator() (const dtype &a,const dtype &b) const {return a<b;}
};

inline int pa(int b){return (b+1)/2-1;}
inline int le(int b){return 2*(b+1)-1;}
inline int ri(int b){return 2*(b+1);}
template<typename dtype,typename compare_type=less_<dtype>>
class pri_queue{
  public:
    pri_queue(vector<dtype>);
    pri_queue(vector<dtype> ,compare_type);
    pri_queue():num_(0){};
    pri_queue(compare_type com):num_(0),com_(com){}
    void push(dtype);
    dtype top(){return data_[0];}
    void pop();
    void build();
    void print_data(){for(auto i:data_)cout<<i<<" ";};
    vector<dtype>* get_data(){return &data_;}
    bool empty(){return num_==0;}
  private:
    vector<dtype> data_;
    compare_type com_;
    int num_ ;
    void down(int i);
};

template<typename dtype,typename compare_type>
pri_queue<dtype,compare_type>::pri_queue(vector<dtype> data){
    data_.swap(data);
    num_ = data_.size(); 
    build();
}

template<typename dtype,typename compare_type>
pri_queue<dtype,compare_type>::pri_queue(vector<dtype> data,compare_type com):com_(com){
    data_.swap(data);
    num_ = data_.size();
    build();
}

template<typename dtype,typename compare_type>
void pri_queue<dtype,compare_type>::push(dtype elem){
    data_.push_back(elem);
    num_++;
    int p = num_-1;
    while(p!=0&&com_(data_[p],data_[pa(p)])){
        dtype tem = data_[p];
	data_[p] = data_[pa(p)];
	data_[pa(p)] = tem;
	p = pa(p);
    }
}
template<typename dtype,typename compare_type>
void pri_queue<dtype,compare_type>::down(int i){
    while(i<=num_/2-1){
        int left = le(i);
        int right = ri(i);
        int min = left;
        if(right<num_&&com_(data_[right],data_[left]))min = right;
        if(com_(data_[min],data_[i])){
        dtype tem = data_[i];
        data_[i] = data_[min];
        data_[min] = tem;
        i = min;
        }else break;
    }
}

template<typename dtype,typename compare_type>
void pri_queue<dtype,compare_type>::pop(){
    data_[0] = data_[num_-1];
    num_--;
    data_.pop_back();
    down(0);
}

template<typename dtype,typename compare_type>
void pri_queue<dtype,compare_type>::build(){
    for(int i=num_/2-1;i>=0;i--){
        down(i);
    }
}

