#include <vector>
#include <limits.h>
#include <iostream>
using namespace std;

template<typename dtype>
struct node{
    dtype weight;
    int key;
    node<dtype>* next;
    node(int key):key(key),weight(dtype(1)),next(nullptr){}
    node(int key,dtype w):key(key),weight(w),next(nullptr){}
};

static const int NIL = INT_MAX;//定义无穷大权重。

template<typename dtype>
class GraphBase{
    public:
      GraphBase(int n1,vector<vector<dtype>> edges);//n1,结点数，n2，边数
      GraphBase(vector<vector<dtype>> adj);
      GraphBase(){}
      virtual ~GraphBase(){}
      vector<int> BFS(int);
      void DFS();
      void print_path(vector<int>,int ,int );//根据前驱子图和结尾的结点来画出路径，两个结点之间的路径
      void print_path(vector<vector<int>>,int,int){}//
      virtual int edge_type(int i,int j){cout<<"只针对有向边"<<endl;}
      virtual vector<int> connected_component(){cout<<"只针对有向边"<<endl;}
      virtual vector<int> topo_sort(){cout<<"只针对有向边"<<endl;}
      virtual void sssp(int s,int type){cout<<"只针对有向边"<<endl;}//该type的意思是算法的不同
      virtual void assp(int type){cout<<"只针对有向边"<<endl;}
      virtual void max_flow(int s,int t){cout<<"只针对有向边"<<endl;}
      virtual void MST(int type){cout<<"只针对无向边"<<endl;}
    protected:
      int num_;
      vector<node<dtype>*> list_graph_;
      vector<vector<dtype>> mat_graph_;
      
      //DFS ,start_t,end_t
      vector<int> start_t_;
      vector<int> end_t_;
      vector<int> dfs_pai_;
      void dfs_iter(int,int&,vector<int>&,vector<int>&,vector<int>&,vector<int>&,vector<node<dtype>*>);

      };

template <typename dtype>
class graph_directed:public GraphBase<dtype>{
    public:
      graph_directed(int n,vector<vector<dtype>> edges):
            GraphBase<dtype>(n,edges){}
      graph_directed(vector<vector<dtype>> adj):
            GraphBase<dtype>(adj){}
      virtual int edge_type(int i,int j);//判断i到j的边，对应0，1，2，3，4。0为无边，1为树边，2：前向边，3：后向边，4：横向边
      virtual vector<int> connected_component();//得到有向图的强连通分量，返回的每一行对应该分量的结点
      virtual vector<int> topo_sort();//对应拓扑排序的顺序

      virtual void sssp(int s,int type);//单源最短路径,path对应最短路径的值，prior_graph对应最短路径的前驱子图
      virtual void assp(int type);//所有结点对的最短路径
      void max_flow(int s,int t){}
      
    private:
      bool sssp_bellman(int s,vector<dtype>& path,vector<int>& prior_graph);//bellman for sssp
      void sssp_dijkstra(int s,vector<dtype>& path,vector<int>& prior_graph);
      void assp_2branch(vector<vector<dtype>>& path_mat,vector<vector<int>>& prior_mat);
      void branch_merge(vector<vector<dtype>>&,vector<vector<dtype>>,vector<vector<int>>&,vector<vector<int>>);
      void assp_floyd(vector<vector<dtype>>& path_mat,vector<vector<int>>& prior_mat);
      void assp_joshan(vector<vector<dtype>>& path_mat,vector<vector<int>>& prior_mat);
      int flow_edmonds(int s,int t){}
};

template <typename dtype>
class graph_undirected:public GraphBase<dtype>{
    public:
      graph_undirected(vector<vector<dtype>> adj){}
      graph_undirected(int n,vector<vector<dtype>> edges){}//该初始化的时候，需要u->v,v->u
      void MST(int type){};

    private:
      vector<int> MST_prim(){}
      vector<int> MST_kruscal(){}
};

//工厂类
template <typename dtype>
class graph{
    public:
    GraphBase<dtype>* create(int type,int n1,vector<vector<dtype>> edges){
        if(type==1)return new graph_directed<dtype>(n1,edges);//1对应无向图
        else return new graph_undirected<dtype>(n1,edges);
    }     
    GraphBase<dtype>* create(int type,vector<vector<dtype>> edges){
        if(type==1)return new graph_directed<dtype>(edges);//1对应无向图
        else return new graph_undirected<dtype>(edges);
    }     
};

template class graph<int>;
template class GraphBase<int>;
template class graph_directed<int>;
