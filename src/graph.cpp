#include "graph.hpp"
#include <queue>
#include <iostream>
/*
 * 广度遍历主要的实现在于用了队列这个数据结构，它所的意思是，想先把同一层的所有元素都
 * 遍历完，再往下面遍历。这也正好符合队列的先进先出的思想，因为我们的算法每一次都是先
 * 遍历了这一层的，再处理下一层的。*/
template <typename dtype>
void Graph<dtype>::BFS(int d){
    //init the attribute for BFS
    color.clear();
    prior.clear();
    distance.clear();
    for(int i=0;i<adj.size();i++){
        if(i==d){
	    color.push_back(BLACK);
	    distance.push_back(0);
	    prior.push_back(ROOT);
	}
	color.push_back(WHITE);
	distance.push_back(INT_MAX);
	prior.push_back(ROOT);
    }
    //init a queue for BFS
    queue<int> Q;
    Q.push(d);
    while(!Q.empty()){
        int tem = Q.front();
	Q.pop();
	dtype * p = adj[tem];
	while(p!=nullptr){
	    if(color[p->key]==BLACK){p=p->next;continue;}
	    Q.push(p->key);
	    distance[p->key] = distance[tem]+1;
	    prior[p->key] = tem;
	    p = p->next;
	}
        color[tem]=BLACK;
    }
}

template <typename dtype>
void Graph<dtype>::print_shortest_path(int i,int j){
    BFS(i);
    vector<int> tem;
    if(distance[j]==INT_MAX)cout<<"no path"<<endl;
    else{
        while(prior[j]!=ROOT){
	    tem.push_back(j);
	    j = prior[j];
	}
    }
    cout<<i;
    for(auto iter = tem.rbegin();iter!=tem.rend();iter++)cout<<"->"<<*iter;
}

template <typename dtype>
void Graph<dtype>::DFS(){
    color.clear();
    prior.clear();
    b_time.clear();
    f_time.clear();
    for(int i=0;i<adj.size();i++){
      color.push_back(WHITE);
      prior.push_back(ROOT);
      b_time.push_back(0);
      f_time.push_back(0);
    }
    time = 0;
    for(int i=0;i<adj.size();i++){
        if(color[i]==WHITE)
		dfs_iter(i);
    }

}
template <typename dtype>
void Graph<dtype>::dfs_iter(int i){
    time++;
    b_time[i] += time;
    color[i]=GREY;
    dtype* p = adj[i];
    while(p!=nullptr){
        if(color[p->key]==WHITE){
	    prior[p->key]=i;
	    dfs_iter(p->key);
	}
	p=p->next;
    }
    color[i]=BLACK;
    time++;
    f_time[i] += time;

}
template <typename dtype>
void Graph<dtype>::print_time()
{
    for(int i=0;i<adj.size();i++){
        cout<<b_time[i];
	cout<<",";
	cout<<f_time[i];
	cout<<" ";
    }
}

template <typename dtype>
void Graph<dtype>::topolo_sort(){
    DFS();
    unordered_map<int,int> map;
    for(int i=0;i<f_time.size();i++)map[f_time[i]]=i;
    sort(f_time.begin(),f_time.end());
    for(auto i=f_time.rbegin();i!=f_time.rend();i++)cout<<map[*i]<<" ";
    cout<<endl;
}

template <typename dtype>
void Graph<dtype>::create_reverse_graph(){
    vector<dtype* > adj_reverse(adj.size());
    for(int i=0;i<adj.size();i++){
        dtype* p = adj[i];
	while(p!=nullptr){
	    if(adj_reverse[p->key]==nullptr){
	        adj_reverse[p->key] = new dtype(i);
	    }
	    else {
	        dtype* q = adj_reverse[p->key];
		adj_reverse[p->key] = new dtype(i);
		adj_reverse[p->key]->next = q;
	    }
	    p = p->next;
	}
    }
    //test
    /*
    for(int i=0;i<adj.size();i++){
        if(adj_reverse[i]==nullptr) cout<<"null"<<endl;
	else{
	    dtype* p = adj_reverse[i];
	    while(p!=nullptr){
	        cout<<p->key<<" ";
		p = p->next;
	    }
	    cout<<endl;
	}
    }
    */
    adj_reverse_.swap(adj_reverse);
}

template <typename dtype>
void Graph<dtype>::sccomponent(){
    DFS();
    create_reverse_graph();
    unordered_map<int,int> map;
    for(int i=0;i<f_time.size();i++)map[f_time[i]]=i;
    sort(f_time.begin(),f_time.end());
    vector<vector<int>> strong_class;
    color.clear();
    for(int i=0;i<adj.size();i++){
        color.push_back(WHITE);
    }
    for(auto i = f_time.rbegin();i!=f_time.rend();i++){
        int id = map[*i];
	vector<int> tree;
	if(color[id]==WHITE)
	{
	    dfs_iter_reverse(id,tree);
	}
	if(!tree.empty())
	    strong_class.push_back(tree);
    }
    for(auto i:strong_class){
        for(auto j:i){
	    cout<<j<<" ";
	}
	cout<<endl;
    }
}

template <typename dtype>
void Graph<dtype>::dfs_iter_reverse(int i,vector<int>& tree){
    time++;
    color[i]=GREY;
    dtype* p = adj_reverse_[i];
    tree.push_back(i);
    while(p!=nullptr){
        if(color[p->key]==WHITE){
	    //prior[p->key]=i;
	    dfs_iter_reverse(p->key,tree);
	}
	p=p->next;
    }
    color[i]=BLACK;

}
