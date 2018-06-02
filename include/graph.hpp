/*
 *基本图算法实现
 *这里的图由邻接链接表法来表示。
 其中链接表用vector<dtype* >来表示，vector中的序号对应的是节点编号，dtype对应邻接表所储存的内容
 至少含有key这个属性h
 图中结点的属性用可以各自属性的数组来表示，边，通过自定义的结构来表示。
 * */
#include <limits.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;
//邻接矩阵，链表结构
struct edge_no_weight{
    int key;
    edge_no_weight* next;
    edge_no_weight(int a):key(a),next(nullptr){}
};
struct edge_with_weight{
    int key;
    int value;
    edge_with_weight* next;
    edge_with_weight(int a,int b):key(a),value(b),next(nullptr){}
};

template<typename dtype>
void print_(vector<dtype*> adj){
for(int i=0;i<adj.size();i++){
        dtype* p = adj[i];
        while(p!=nullptr){
	    cout<<p->key<<" ";
	    p = p->next;
	}
	cout<<endl;
    }
}


typedef int COLOR;
const int WHITE =0;
const int BLACK =1;
const int GREY =2;
const int ROOT = -1;
template <typename dtype>
class Graph{
    public:
      Graph(vector<dtype *> x):adj(x){}
      void BFS(int d);//广度优先搜索
      void print_shortest_path(int i,int j);
      void DFS();//深度优先搜索
      void dfs_iter(int i);
      void dfs_iter_reverse(int i,vector<int>& tree);
      void print_time();
      void topolo_sort();//拓扑排序
      void sccomponent();//强连通分量。
      virtual void create_reverse_graph()=0;//创建转置图
    protected:
      vector<dtype *> adj;
      vector<dtype *> adj_reverse_;
      //BFS attribute of the node
      vector<COLOR> color;
      vector<int> distance;
      vector<int> prior;
      //DFS attribute of the node
      vector<int> b_time;//the time when fisrt meet the node
      vector<int> f_time;//the time when all ajd of node finish
      int time;
};
template <typename dtype>
class Graph_no_weight:public Graph<dtype>{
    public:
	    Graph_no_weight(vector<dtype*> x):Graph<dtype>(x){}
    private:
	    void create_reverse_graph();
};
template <typename dtype>
class Graph_with_weight:public Graph<dtype>{
    public:
	    Graph_with_weight(vector<dtype*> x):Graph<dtype>(x){}
            vector<dtype*> MST_prim();//最小生成树，针对无向图
            vector<dtype*> MST_krusal();
    private:
	    void create_reverse_graph();
};
template class Graph_no_weight<edge_no_weight>;
template class Graph_with_weight<edge_with_weight>;
