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
    queue<int> q;//
    q.push(s);
    flag[s]=1;
    while(!q.empty()){
        int c = q.front();
        q.pop();
        node<dtype>* tem = list_graph_[c];
        while(tem!=nullptr){
            int p = tem->key;
            if(!flag[p]){
                pai[p] = c;
                q.push(p);
                flag[p] = 1;
            }
            tem = tem->next;
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
    for(int i=0;i<this->num_;i++){
        node<dtype>* tem = this->list_graph_[i];
        while(tem!=nullptr){
            int v = tem->key;
            if(d[i] + tem->weight <d[v])return false;
            tem = tem->next;
        }
    }
    return true;
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

/*
   直接输出，最短路径矩阵和前驱子图矩阵作为最后的结果
   type:不同的算法：1:重复二分法，  2.floyd     3.johnson
*/
template<typename dtype>
void graph_directed<dtype>::assp(int type){
    //init path_mat;
    vector<vector<dtype>> path_mat(this->num_,vector<dtype>(this->num_,NIL));
    for(int i=0;i<this->num_;i++)path_mat[i][i] = 0;
    //init prior_mat;
    vector<vector<int>> prior_mat(this->num_,vector<dtype>(this->num_,NIL));
    if(type==1)assp_2branch(path_mat,prior_mat);
    else if(type==2)assp_floyd(path_mat,prior_mat);
    else assp_joshan(path_mat,prior_mat);
    for(int i=0;i<this->num_;i++){
        cout<<endl;
        for(int j=0;j<this->num_;j++){
            cout<<path_mat[i][j]<<" ";    
        }
        cout<<"  ";
        for(int j=0;j<this->num_;j++){
            cout<<prior_mat[i][j]<<" ";
        }
    }
}

/*
    算法思路：假设问题p[k]表示的是，每条路径至多包含k个结点的时候的所有点的最短路径的矩阵。
    那么显然当p[num_]即对应的是我们的最终的解。构造最优解p(i,j)[k] = min(p(i,j)[k-1],p(i,k)[k-1]+weight(k,j))对于所有可能的k
    由于实际上我们要求的仅仅是p[num_]，中间的其他的起始并不需要，所以我们可以直接用二分法。书上这里是类比了矩阵运算来解释这一点的
*/
template<typename dtype>
void graph_directed<dtype>::assp_2branch(vector<vector<dtype>> &p,vector<vector<int>> &pai){
    //初始化p和pai
    p = this->mat_graph_;
    
    for(int i=0;i<this->num_;i++){
        p[i][i] = 0;
        for(int j=0;j<this->num_;j++)
        {
            if(p[i][j]!=NIL&&i!=j){
               pai[i][j] = i;
            }    
        }
    }
    int i=1;
    while(i<this->num_){
        branch_merge(p,p,pai,pai);
        i *=2;
    }
}
/*
  该函数是上面算法的辅助函数，其即是将p这个当前解，加上q步的解。
  pai对应的是p对应的前驱子图。
  paiq对应的是q对应的前驱子图。
*/
template<typename dtype>
void graph_directed<dtype>::branch_merge(vector<vector<dtype>> &p,vector<vector<dtype>> q,\
                                          vector<vector<int>> &pai,vector<vector<int>> paiq){
    for(int i=0;i<this->num_;i++){
        for(int j=0;j<this->num_;j++){
            for(int k=0;k<this->num_;k++){
                if(p[i][k]!=NIL&&p[i][j]-p[i][k]>q[k][j])//这里是为了防止INT_MAX加上某个数会溢出.
                {
                    p[i][j] = p[i][k]+q[k][j];
                    pai[i][j] = paiq[k][j];
                }
            }    
        }
     
    }    
}

/*
floyd算法的复杂度为O(V^3),重复二分法的为O(V^3LOGV),最主要的原因在于重复二分法中的最优子结构计算的时候还需要一次遍历。
这里floyd算法找到了另外一个最优子结构。假设p[k]表示的是i到j结点的中间结点由v1,v2...vk这k个结点的集合中的结点构成的最短路径。
p(i,j)[k] = min(p(i,j)[k-1],p(i,vk)[k-1]+p(vk,j)[k-1]),这里对应p[this->num_]即为最后的结果
*/
template<typename dtype>
void graph_directed<dtype>::assp_floyd(vector<vector<dtype>> &p,vector<vector<int>> &pai){
    //初始化path
    p = this->mat_graph_;
    for(int i=0;i<this->num_;i++){
        p[i][i] = 0;
        for(int j=0;j<this->num_;j++)
        {
            if(p[i][j]!=NIL&&i!=j){
               pai[i][j] = i;
            }    
        }
    }
    for(int k=0;k<this->num_;k++){
        for(int i=0;i<this->num_;i++){
            for(int j=0;j<this->num_;j++){
                if(p[i][k]!=NIL&&p[k][j]!=NIL&&p[i][j]>p[i][k]+p[k][j])    
                {
                    p[i][j] = p[i][k] + p[k][j];
                    pai[i][j] = pai[k][j];
                }
            }    
        }
    }

}

/*
   joshan 算法：该算法是用在稀疏图上的，其算法复杂度为O(V^2lgV+VE),对于稀疏图来说E几乎就是常数级别的。
   该算法的主要思想 就是将所有的权重重新赋值为非负权重，然后对于每一个结点用dijkstra来进行单源操作。
   dijkstra的算法复杂度最低为O(VlgV+E).
   该算法的重点在于如何将所有的权重改成非负权重，并且保证修改后的图和之前的图最短路径是一致的。
   这里对(u,v)边，wei'(u,v) = wei(u,v) + h(u) - h(v),这样重构的权重就是满足和之前权重的最短路径是一样的。h对应任意函数。
   而这个时候为了构造一个函数h是的重构的权重满足非负，这里引入了一个新的结点s，其到其他所有结点权重为0。这样s到其他结点的单源
   最优路径作为这个里的h，由三角不等式满足：h(u)+wei(u,v)>h(v),所以这个时候wei'(u,v)即是非负的
*/
template<typename dtype>
void graph_directed<dtype>::assp_joshan(vector<vector<dtype>>& p,vector<vector<int>>& pai){
    //引入新结点，先暂时的在list_graph上加入新结点，暂时将该图变成新的图‘
    this->list_graph_.push_back(new node<dtype>(0,0));
    node<dtype>* tem2 = this->list_graph_[this->num_];
    for(int i=1;i<this->num_;i++){
        tem2->next = new node<dtype>(i,0);
        tem2 = tem2->next;
    }
    //暂时将this->num_加1，因为这个时候还是要弄到内部的bellman算法。
    this->num_++;
    vector<dtype> d(this->num_,NIL);//此时的新结点的单源最优路径
    d[this->num_-1] = 0;
    vector<int> tem_pai(this->num_,NIL);
    if(!sssp_bellman(this->num_-1,d,tem_pai))cout<<"有负数环"<<endl;
    this->num_--;
    this->list_graph_.pop_back();
    d.pop_back();
    //更新权重
    for(int i=0;i<this->num_;i++){
        node<dtype>* tem = this->list_graph_[i];
        while(tem!=nullptr){
            tem->weight += d[i]-d[tem->key];
            tem = tem->next;
        }
    }

    for(int i=0;i<this->num_;i++){
        sssp_dijkstra(i,p[i],pai[i]);    
    }
    //恢复权重
    for(int i=0;i<this->num_;i++){
        node<dtype>* tem = this->list_graph_[i];
        while(tem!=nullptr){
            tem->weight -= d[i]-d[tem->key];
            tem = tem->next;
        }
    }
}

template<typename dtype>
void graph_directed<dtype>::max_flow(int source,int target)
{
    flow_edmonds(source,target);
}
/*
    最大流问题的解法：构造残存网络，在残存网络中找到一条增广路径，然后流增加，再重复上面的过程
    edmonds算法的改进在于，在找增广路径的时候，是在找源结点到汇结点的最短路径（这个最短路径是相对于权重为1来说的）
    ---这里会遇到一个设计上的问题，比如说，现在我们要获取一个权重都为1的图，这个时候，现在我们的算法也是在图这个类里面
    这个时候可以建立这个对象???这个时候貌似可以定义一个graph base类来处理。所以说，我们可以在基类中放一些，我们后面要用到
    的函数比如DFS或者其他的。
*/
template <typename dtype>
void graph_directed<dtype>::flow_edmonds(int source,int target){
    //这里残存网络用mat来表示
    vector<vector<dtype>> graph_resdual = this->mat_graph_;
    //这里用map来存储边以及该边上的流
    auto pairhash = [](const pair<int,int> &a){
        size_t b = a.first;
        size_t c = a.second;
        return b^(c<<32);};
    auto com = [](const pair<int,int> &a,const pair<int,int> &b){return a.first==b.first&&a.second==b.second;};
    unordered_map<pair<int,int>,dtype,decltype(pairhash),decltype(com)> edge_flow(10,pairhash,com); 
    for(int i=0;i<this->num_;i++){
        node<dtype>* tem = this->list_graph_[i];
        while(tem!=nullptr)
        {
            edge_flow[make_pair(i,tem->key)] = dtype(0);
            tem = tem->next;    
        }
    }
    vector<int> pai;
    while(exist_path(graph_resdual,source,target,pai)){
        //根据此时的前驱 pai，来找到最短的路径 (source->target)
        int v = target;
        dtype min = NIL;
        while(pai[v]!=NIL){
            int u = pai[v];
            if(graph_resdual[u][v]<min){
                min = graph_resdual[u][v];
            }
            //test
            if(graph_resdual[u][v]==NIL)cout<<"错误";
            v = u;
        }
        //update flow and graph_resdual
        v = target;
        while(pai[v]!=NIL){
            int u = pai[v];
            if(edge_flow.find(make_pair(u,v))!=edge_flow.end()){
                edge_flow[make_pair(u,v)] += min;
                graph_resdual[u][v] -= min;
                graph_resdual[u][v] = graph_resdual[u][v]==0?NIL:graph_resdual[u][v];
                graph_resdual[v][u] = graph_resdual[v][u]==NIL?min:graph_resdual[v][u] + min;
            }else {
                edge_flow[make_pair(v,u)] += min;
                graph_resdual[v][u] -= min;
                graph_resdual[v][u] = graph_resdual[v][u]==0?NIL:graph_resdual[v][u];
                graph_resdual[u][v] = graph_resdual[u][v]==NIL?min:graph_resdual[u][v] + min;
            }
            v = u;
        }
    }
    //显示最大流
    int result=0;
    for(auto iter:edge_flow){
        cout<<iter.first.first<<"->"<<iter.first.second<<" "<<iter.second<<endl;    
        if(iter.first.first==0)result += iter.second;
        if(iter.first.second==0)result -= iter.second;
    }
    cout<<"max flow:"<<result<<endl;
}

template<typename dtype>
bool graph_directed<dtype>::exist_path(vector<vector<dtype>> g,int s,int t,vector<int> &pai){
    GraphBase<dtype> c(g);
    pai = c.BFS(s);
    while(t!=s){
        if(pai[t]==NIL)return false;
        else t = pai[t];
    }
    return true;
}

int main(){
    //vector<int> num;
    //GraphBase<int> c(2,)
    graph<int> graph;
    //GraphBase<int> *c = graph.create(1,7,vector<vector<int>>{{0,1},{0,2},{0,3},{2,3},{1,3},{3,1},{3,0},{0,4},{4,5},{5,6}});
    //GraphBase<int> *c = graph.create(1,5,vector<vector<int>>{{0,1,3},{0,2,5},{1,2,2},{2,1,1},{1,4,6},{2,4,4},{4,3,2},\
                                                              {3,4,7},{3,0,3},{2,3,6}});
    //GraphBase<int> *c = graph.create(1,5,vector<vector<int>>{{0,1,3},{0,4,-4},{0,2,8},\
                                                             {1,4,7},{1,3,1},\
                                                             {2,1,4},\
                                                             {3,0,2},{3,2,-5},\
                                                             {4,3,6}});
    GraphBase<int> *c = graph.create(1,6,vector<vector<int>>{{0,1,16},{0,2,13},
                                                             {1,3,12},
                                                             {2,4,14},{2,1,4},
                                                             {3,2,9},{3,5,20},
                                                             {4,3,7},{4,5,4}});
    //c->DFS();
    //GraphBase<int>* c = graph.create(1,vector<vector<int>>{{0,1},{2,0}});
    /*
    c->print_path(c->BFS(0),0,3);
    c->DFS();
    cout<<c->edge_type(0,3);
    cout<<endl;
    vector<int> topo = c->topo_sort();
    vector<int> componnet = c->connected_component();
    c->sssp(0,1);
    c->sssp(0,2);
    */
    //c->assp(1);
    //c->assp(2);
    //c->assp(3);
    c->max_flow(0,5);
}

