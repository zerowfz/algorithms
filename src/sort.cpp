#include "sort.hpp"
const float MAX=99999.99;
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
  //cout<<ls_done[i]<<endl;
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

void MergeSort::sort(float *A,int s,int f)
{
 if (s<f)
 {
 int m = (s+f)/2;
 //cout<<s<<','<<m<<','<<f<<endl;
 sort(A,s,m);
 sort(A,m+1,f);
 merge(A,s,m,f);
 }
}

void MergeSort::merge(float*A,int s,int m,int f)
{
 float*L =new float[m-s+2];
 float*R = new float[f-m+1];
 int i;
 int j;
 for (i=0;i<=m-s;i++)L[i]=A[i+s];
 L[i]=MAX;
 for (j=0;j<=f-m-1;j++)R[j]=A[j+m+1];
 R[j]=MAX;
 i=0;j=0;
 for(int k=s;k<=f;k++)
 {
  if(L[i]<R[j])
  {
   A[k]=L[i];
   i++;
   //cout<<A[k]<<endl;
  }
  else
  {
   A[k]=R[j];
   j++;
   //cout<<A[k]<<endl;
  }
 }
}
