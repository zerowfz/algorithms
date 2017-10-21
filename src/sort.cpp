#include "sort.hpp"
/*
int main()
{
 float ls[] ={1.0,5.0,2.0,6.0,8.0,23.0};
 cout<<sizeof(ls)/sizeof(ls[0]);
 InsertSort sort(ls,6);
 sort.output();
 sort.process();
 sort.output();
 cout<<ls<<endl;
}
*/
sortbase::sortbase(float*A,int N)
{
 ls_ = A;
 num_array =  N;
 ls_done = new float[num_array]; 
 for(int i=0;i<N;i++)
 {
  ls_done[i] = ls_[i];
 }
}

void InsertSort::insert(float *ls)
{
 int j;
 float key;
 for(int i=1;i<num_array;i++)
 {
  key = ls[i];
  j=i-1;
  while(j>=0&&ls[j]>key)
  {
   ls[j+1]=ls[j];
   j=j-1;
  }
  ls[j+1]=key;
 }
}
