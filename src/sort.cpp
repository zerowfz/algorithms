#include "sort.h"
extern const float MAX=99999.99;
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
	:ls_(A),num_array(N),ls_done(0)
	 //初始化列表，来给常量变量来进行初始化，而不是赋值。
{
 ls_done = new float[num_array]; 
 for(int i=0;i<N;i++)
 {
  ls_done[i] = ls_[i];
  //cout<<ls_done[i]<<endl;
 }
}

void InsertSort::insert()
{
 int j;
 float key;
 for(int i=1;i<num_array;i++)
 {
  key = ls_done[i];
  j=i-1;
  while(j>=0&&ls_done[j]>key)
  {
   ls_done[j+1]=ls_done[j];
   j=j-1;
  }
  ls_done[j+1]=key;
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

void HeapSort::process()
{
 heap_.build_max_heap();
 //每次将最大值即a[0]与当前最后的一个值交换位置，执行最大堆操作
 float tem=0;
 for(int i=num_array-1;i>0;i--)
 {
  tem =ls_done[i];
  ls_done[i]=ls_done[0];
  ls_done[0]=tem;
  heap_.length--;
  heap_.layer=heap_.get_layer(heap_.layer);
  heap_.max_heap(1);
 }
}

void QuickSort::quicksort(float *A,int p,int r)
{
 if(p<r)
 {
  int q=patition(A,p,r);
  cout<<q<<endl;
  quicksort(A,p,q-1);
  quicksort(A,q+1,r);
 }
 return;
}

int QuickSort::patition(float*A,int p,int r)
{
 //储存主元的值
 float x = A[r];
 //i:记录某个位置，这个位置之前的值都是小于主元的，之后的值都是大于主元的
 int i = p;
 float temp;
 for(int j=p;j<r;j++)
 {
  if(A[j]<=x)
  {
   //这个时候要交换A[j]与A[i]的位置，因为i记录的是前面都是小于x的元素，
   //实际上也可以这样理解，也就是把所有小于x的元素顺着写下来。
   if(x==j) i++;
   else
   {
    temp = A[j];
    A[j] = A[i];
    A[i] = temp;
    i++;
   }
  }
 }
 //交换主元的位置
 A[r]=A[i];
 A[i]=x;
 return i;
}
