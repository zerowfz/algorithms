#include "graph.hpp"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    //vector<no_weight* > adj;
     
    //定义了一个输入adj的，输入格式，数字碰见-1说明，调到下一个节点的边。
    //例如{1,3,-1,4,-1,5,4,-1,1,-1,3-1,5,-1}表示的就是
    //{
    //0   1,3
    //1   4
    //2   5,4
    //3   1
    //4   3
    //5   5
    //这样的一个邻接表
    //}
    /*
    vector<int> input{1,3,-1,4,-1,5,4,-1,1,-1,3,-1,5,-1};
    int size = 6;
    int j=0;
    for (int i=0;i<size;i++){
	if(input[j]==-1){adj.push_back(nullptr);j++;}
	else{
	    no_weight* p = new no_weight(input[j]);
	    no_weight* tem = p;
	    cout<<input[j]<<" ";
            while(input[j+1]!=-1){
		j++;
	        tem->next = new no_weight(input[j]);
		tem = tem->next;
		cout<<input[j]<<" ";
	    }
	    j+=2;
	    cout<<endl;
	    adj.push_back(p);
	}
    }  
    Graph<no_weight> gra(adj);
    gra.print_shortest_path(0,3);
    gra.DFS();
    gra.print_time();
    */
    /*测试topolo_sort(),即有向无环图的拓扑排序
    vector<int> input{1,2,-1,3,-1,3,-1,-1,5,7,-1,1,7,-1,7,-1,-1,-1};
    int size = 9;
    int j=0;
    for (int i=0;i<size;i++){
	if(input[j]==-1){adj.push_back(nullptr);j++;}
	else{
	    no_weight* p = new no_weight(input[j]);
	    no_weight* tem = p;
	    cout<<input[j]<<" ";
            while(input[j+1]!=-1){
		j++;
	        tem->next = new no_weight(input[j]);
		tem = tem->next;
		cout<<input[j]<<" ";
	    }
	    j+=2;
	    cout<<endl;
	    adj.push_back(p);
	}
    }  
    Graph<no_weight> gra(adj);
    //gra.topolo_sort();*/
    //测试强连接分量
//    vector<int> input{1,-1,2,4,5,-1,3,6,-1,7,2,-1,0,5,-1,6,-1,5,7,-1,7,-1};
//    int size = 8;
//    int j=0;
//    for (int i=0;i<size;i++){
//	if(input[j]==-1){adj.push_back(nullptr);j++;}
//	else{
//	    no_weight* p = new no_weight(input[j]);
//	    no_weight* tem = p;
//	    cout<<input[j]<<" ";
//            while(input[j+1]!=-1){
//		j++;
//	        tem->next = new no_weight(input[j]);
//		tem = tem->next;
//		cout<<input[j]<<" ";
//	    }
//	    j+=2;
//	    cout<<endl;
//	    adj.push_back(p);
//	}
//    }  
//    Graph<no_weight> gra(adj);
//    gra.sccomponent();
    //无向图输入
    //第一行：结点数目，边个数
    //第二行开始为对应边的 如1 2 3 表示，1与2相连，3为边权重
    int n,edge;
    ifstream fin("test.txt");
    fin>>n>>edge;
    vector<edge_with_weight*> adj(n,nullptr);
    int node1,node2,weight;
    for(int i=0;i<edge;i++){
        fin>>node1>>node2>>weight;
	if(adj[node1]==nullptr)
		adj[node1] = new edge_with_weight(node2,weight);
	else {
		edge_with_weight* p = adj[node1];
		adj[node1] = new edge_with_weight(node2,weight);
	        adj[node1]->next = p;}
	if(adj[node2]==nullptr)
		adj[node2] = new edge_with_weight(node1,weight);
	else {
		edge_with_weight* p = adj[node2];
		adj[node2] = new edge_with_weight(node1,weight);
	        adj[node2]->next = p;
        }
    }

    Graph_with_weight<edge_with_weight> graph(adj);
    vector<edge_with_weight*> p = graph.MST_krusal(); 
    print_(p);

}

