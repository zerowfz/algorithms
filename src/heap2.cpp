#include "heap2.h"
int main()
{
   struct elem{
   int key;
   int data;
   elem(int a,int b):key(a),data(b){}
   };
   vector<elem> d{elem(1,3),elem(2,4),elem(3,2),elem(4,6),elem(5,9),elem(6,7)};
   pri_queue<int> a(vector<int>{3,4,2,6,9,7});
   auto com = [](elem a,elem b){return a.data<b.data;};
   pri_queue_unique<elem,decltype(com)> c(d,com);
   a.print_data(); 
   cout<<endl;
   //c.print_data();
   //c.update_hash();
   //c.find()
   c.update_hash();
   vector<elem>* output = c.get_data();
   cout<<(*output)[c.find(3)].key<<(*output)[c.find(3)].data<<c.find(3);
   /*
   auto fun = [](int a,int b){return a>b;};
   pri_queue<int,decltype(fun)> b(vector<int>{3,4,2,6,9,7},fun);
   b.print_data();
   cout<<endl;
   cout<<b.top()<<endl;
   b.pop();
   b.print_data();
   */
}
