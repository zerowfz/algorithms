#include "graph2.h"
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <utility>

using namespace std;

template<typename dtype>
GraphBase<dtype>::GraphBase(int n1,vector<vector<dtype>> edges):num_(n1){
   list_graph_ = vector<node<dtype>*> (n1);
   mat_graph_ = vector<vector<dtype>> (n1,vector<dtype> (n1,NIL));
   int c = edges[0].size();//if c>2说明，是权重非1，如果等于2，权重为1.
   int k = edges.size();
   if(c==2){
       for(int i=0;i<k;i++){
           int id1 = int(edges[i][0]);
           int id2 = int(edges[i][1]);
           if(list_graph_[id1]==nullptr)list_graph_[id1] = new node<dtype>(id2);
           else {
               //链表的插入操作，插入到前面
               node<dtype> *tem = list_graph_[id1];
               list_graph_[id1] = new node<dtype>(id2);
               list_graph_[id1]->next = tem;
           }
           mat_graph_[id1][id2] = 1;
       }
   }else{
        for(int i=0;i<k;i++){
           int id1 = int(edges[i][0]);
           int id2 = int(edges[i][1]);
           if(list_graph_[id1]==nullptr)list_graph_[id1] = new node<dtype>(id2,edges[i][2]);
           else
           {
               node<dtype>* tem = list_graph_[id1];
               list_graph_[id1] = new node<dtype>(id2,edges[i][2]);
               list_graph_[id1]->next = tem;
           }
           mat_graph_[id1][id2] = edges[i][2];
       }
   }
}

template <typename dtype>
GraphBase<dtype>::GraphBase(vector<vector<dtype>> edges):num_(edges.size()){
    list_graph_ = vector<node<dtype>* > (num_);
    for(int i=0;i<num_;i++){
        for(int j=0;j<num_;j++){
            if(edges[i][j]!=NIL){
                if(list_graph_[i]==nullptr)list_graph_[i] = new node<dtype>(j,edges[i][j]);
                else {
                    //链表的插入操作，插入到前面
                    node<dtype> *tem = list_graph_[i];
                    list_graph_[i] = new node<dtype>(j,edges[i][j]);
                    list_graph_[i]->next = tem;
                }
            }    
        }
    }
    mat_graph_.swap(edges);
}

template <typename dtype>
vector<int> GraphBase<dtype>::BFS(int s){
    vector<int> flag(num_,0);//判断结点是否已经遍历过
    vector<int> pai(num_,NIL);//返回的前驱子图；
    queue<node<dtype>*> q;//
    q.push(list_graph_[s]);
    pai[q.front()->key] = s;
    flag[q.front()->key] = 1;
    while(!q.empty()){
        node<dtype>* tem = q.front();
        q.pop();
        while(tem->next!=nullptr){
            int p = tem->key;
            tem = tem->next;
            if(flag[tem->key])continue;
            else{
                pai[tem->key] = p;
                q.push(tem);
                flag[tem->key] = 1;
            }
        }
    }
    return pai;
}

template<typename dtype>
void GraphBase<dtype>::print_path(vector<int> pai,int i,int j){
    vector<int> tem;
    int end = j;
    while(i!=j){
        if(j==NIL){
            cout<<"不存在"<<i<<"到"<<end<<"的路径"<<endl;
            return;
        }
        tem.push_back(j);
        j = pai[j];
    }
    tem.push_back(i);
    for(auto i = tem.rbegin();i!=tem.rend();++i){
        cout<<*i<<" ";
    }
    cout<<endl;
}
//DFS函数，对所有的结点都深度遍历一次，这里的目的只是为了计算，每个结点的开始事件和截止时间
//为了后面的操作使用

template<typename dtype>
void GraphBase<dtype>::DFS()
{
    //init the 每个结点的初始时间，结束时间
    start_t_ = vector<int> (num_,0);
    end_t_ = vector<int> (num_,0);
    dfs_pai_ = vector<int> (num_,NIL);
    vector<int> flag(num_,0);
    int time = 0;
    for(int i=0;i<num_;i++){
        if(flag[i]==1)continue;
        dfs_iter(i,time,flag,start_t_,end_t_,dfs_pai_,list_graph_);
    }
}

template<typename dtype>
void GraphBase<dtype>::dfs_iter(int i,int &time,vector<int> &flag,vector<int> &start_t_,\
                                        vector<int>& end_t_,vector<int>& dfs_pai_,\
                                        vector<node<dtype>*> list_graph_){
    time +=1;
    start_t_[i] = time;
    node<dtype>* p = list_graph_[i];
    flag[i] = 1;
    while(p!=nullptr){
        if(flag[p->key]==0){
            dfs_pai_[p->key] = i;
            dfs_iter(p->key,time,flag,start_t_,end_t_,dfs_pai_,list_graph_);
        }
        p = p->next;
    }
    time ++;
    end_t_[i] = time;
}

/*
   边的分类，实际上可以直接根据,dfs得到的信息来直接判断。
   这里没有用树中的，在DFS过程中，根据第一次边的颜色来判断。
   而是通过前驱子图来判断，对于深度搜索得到的前驱子图，它实际上表示的是，这一个深度搜索的路径，
   因此对于边(u,v)如果
   1.v.pai = u,则说明边为该深度搜索下的树边
   2.v.end_t_ < u.end_t_&& v.start_t_>u.end_start_ 这个条件说明，v在u的搜索路径中，此时(u->v)肯定就是前向边了
   3.反过来如果u.start_t,u.end_t_在v.start_t_,v.end_t_内部的那么(u,v)对应肯定就是后向边了
   4.其他情况即是横向边。
*/
template<typename dtype>
int graph_directed<dtype>::edge_type(int i,int j){
    if(this->mat_graph_[i][j]==NIL)return 0;
    if(this->dfs_pai_[j]==i)return 1;
    else if(this->start_t_[i]<this->start_t_[j]&&this->end_t_[i]>this->end_t_[j])return 2;
    else if(this->start_t_[i]>this->start_t_[j]&&this->end_t_[i]<this->end_t_[j])return 3;
    else return 4;

}

template<typename dtype>
vector<int> graph_directed<dtype>::topo_sort(){
    auto com = [](pair<int,int> a,pair<int,int> b){return a.first<b.first;};
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(com)> q(com);
    for(int i=0;i<this->num_;i++){
        q.push(make_pair(this->end_t_[i],i));
    }
    vector<int> result;
    for(int i=0;i<this->num_;i++){
        result.push_back(q.top().second);
        q.pop();
    }
    return result;
}

/*
    强连通分量指的是这份量中的任意两个边都是彼此可以到达的。
    其可以通过end_t_来判断，属于两个分量的结点u,v如果存在边(u,v)那么end_t_[u]>end_t_[v],
    所以对于图的转置图，如果(u,v)属于转置图中，则end_t_[u]<end_t_[v],这个也就是说v这个分量所有的结点，都不可能通向
    u这个分量所有的结点，所以对v这个结点做一次深度遍历既可以找到该分量所有的结点。
    输出：pai前驱子图，我们可以通过这个前驱子图很容易得到各个分量的元素。首先pai中NIL的元素的个数即对应分量的个数
    然后可以到该结点的结点即属于这个分量的。
*/
template<typename dtype>
vector<int> graph_directed<dtype>::connected_component(){
    //get the transposed graph.
    vector<node<dtype>*> trans(this->num_,nullptr);//转置图
    for(int i=0;i<this->num_;i++){
        node<dtype>* p = this->list_graph_[i];
        while(p!=nullptr){
            int j = p->key;
            if(trans[j]==nullptr)trans[j] = new node<dtype>(i);
            else{
                node<dtype>* tem = trans[j];
                trans[j] = new node<dtype>(i);
                trans[j]->next = tem;
            }
            p = p->next;
        }
    }
    //DFS for origianl G,sort 
    unordered_map<int,int> end2key;
    for(int i=0;i<this->num_;i++)end2key[this->end_t_[i]] = i;
    vector<int> tem = this->end_t_;
    sort(tem.begin(),tem.end());
    //dfs for transposed G 
    vector<int> flag(this->num_,0);
    vector<int> a(this->num_,0); 
    vector<int> b(this->num_,0);
    vector<int> pai(this->num_,NIL);
    int time = 0;
    for(auto i=tem.rbegin();i!=tem.rend();i++){
        int k = end2key[*i];
        if(flag[k]==1)continue;
        else this->dfs_iter(k,time,flag,a,b,pai,trans);
    }
    return pai;
} 

/*
   输入：s  源结点
         type 使用的算法  1.bellman法  2.dijkstra法 
*/
template<typename dtype>
void graph_directed<dtype>::sssp(int s,int type){
    vector<dtype> path(this->num_,NIL);
    path[s] = 0;
    vector<int> pai(this->num_,NIL);
    if(type==1){
        bool notneg = sssp_bellman(s,path,pai);
        if(!notneg)cout<<"有负数环"<<endl;
    }else{
        sssp_dijkstra(s,path,pai);    
    }
    for(int i=0;i<this->num_;i++){
        this->print_path(pai,s,i);
        cout<<path[i]<<endl;
    }
}
/*
bellman法来解决单源最短路径想法：
利用松弛法(更新s,v之间的最短路径)
*/
template<typename dtype>
bool graph_directed<dtype>::sssp_bellman(int s,vector<dtype> &d,vector<int> &p){
    for(int i=0;i<this->num_-1;i++){
        //遍历边
        for(int j=0;j<this->num_;j++){
            node<dtype>* tem = this->list_graph_[j];
            while(tem!=nullptr){
                int v = tem->key;
                if(d[j]!=NIL&&d[j]+tem->weight<d[v]){
                    //松弛
                    d[v] = d[j] + tem->weight;
                    p[v] = j;
                }
                tem = tem->next;
            }
        }
    }    
    //判断是否有负数环
}
/*
dijkstra算法来解决单源最短路径问题，不过该方法要求权重不能有负数。
该方法使用的是贪心策略，我们每一次都是选择当前最优路径最小的到集合S中，
然后对该结点的所有边做松弛，再重复这个过程。我们可以证明出，这样选择的最小路径的结点，其
此时的路径即为其的最小路径。
*/
template<typename dtype>
void graph_directed<dtype>::sssp_dijkstra(int sor,vector<dtype> &d,vector<int> &p){
    //这里不用堆来存储数据了，就直接用一个num_的数组来储存相应结点的当前的最小路径
    //如果要删除的话，则用另外一个set记录一下。
    unordered_set<int> s;//记录已经是最优路径的结点集合
    while(s.size()<this->num_){
        //找到d中最小的结点
        int min = NIL;
        int newNode;
        for(int i=0;i<d.size();i++){
            if(s.find(i)==s.end()){
                if(d[i]<=min){
                    min = d[i];
                    newNode = i;
                }    
            }    
        }
        s.insert(newNode);
        //松弛所有的newNode的边
        node<dtype>* tem = this->list_graph_[newNode];
        while(tem!=nullptr)
        {
            if(d[newNode]+tem->weight<d[tem->key]){
                d[tem->key] = d[newNode] + tem->weight;
                p[tem->key] = newNode;
            }    
            tem = tem->next;
        }
    }
}

template<typename dtype>
void graph_directed<dtype>::assp(){

}

int main(){
    //vector<int> num;
    //GraphBase<int> c(2,)
    graph<int> graph;
    //GraphBase<int> *c = graph.create(1,7,vector<vector<int>>{{0,1},{0,2},{0,3},{2,3},{1,3},{3,1},{3,0},{0,4},{4,5},{5,6}});
    GraphBase<int> *c = graph.create(1,5,vector<vector<int>>{{0,1,3},{0,2,5},{1,2,2},{2,1,1},{1,4,6},{2,4,4},{4,3,2},\
                                                              {3,4,7},{3,0,3},{2,3,6}});
    //GraphBase<int>* c = graph.create(1,vector<vector<int>>{{0,1},{2,0}});
    c->print_path(c->BFS(0),0,3);
    c->DFS();
    cout<<c->edge_type(0,3);
    cout<<endl;
    vector<int> topo = c->topo_sort();
    vector<int> componnet = c->connected_component();
    c->sssp(0,1);
    c->sssp(0,2);
}

