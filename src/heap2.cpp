#include "heap2.h"
int main()
{
   pri_queue<int> a(vector<int>{3,4,2,6,9,7});
   a.print_data(); 
   auto fun = [](int a,int b){return a>b;};
   pri_queue<int,decltype(fun)> b(vector<int>{3,4,2,6,9,7},fun);
   b.print_data();
   cout<<endl;
   cout<<b.top()<<endl;
   b.pop();
   b.print_data();
}
