/*
 *基本图算法实现
 *这里的图由邻接链接表法来表示。
 其中链接表用vector<dtype* >来表示，vector中的序号对应的是节点编号，dtype对应邻接表所储存的内容
 至少含有key这个属性h
 * */
#include <limits.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
//邻接矩阵，链表结构
struct no_weight{
    int key;
    no_weight* next;
    no_weight(int a):key(a),next(nullptr){}
};
typedef int COLOR;
const int WHITE =0;
const int BLACK =1;
const int GREY =2;
const int ROOT = -1;
template <typename dtype>
class Graph{
    public:
      Graph(vector<dtype *> x):adj(x){}
      void BFS(int d);
      void print_shortest_path(int i,int j);
      void DFS();
      void dfs_iter(int i);
      void dfs_iter_reverse(int i,vector<int>& tree);
      void print_time();
      void topolo_sort();
      void sccomponent();
      void  create_reverse_graph();
    private:
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
template class Graph<no_weight>;
