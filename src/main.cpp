#include "heap2.h"
int main()
{
   auto fun = [](int a,int b){return a>b;};
   CREATE_PRI_QUEUE(int,decltype(fun));
   pri_queue<int,decltype(fun)> b(vector<int>{3,4,2,6,9,7},fun);
   b.print_data();
}
