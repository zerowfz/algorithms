#include "heap.hpp"
inline int POW_2(int n){ int x=1;while(n>0){x*=2;n--;}}
inline int heap::get_layer(int n)
{
 int layer=0;
 int x=1;
 while(n>=x)
 {
  x *=2;
  layer++;
 }
 return layer;
}

heap::max_heap(int i)
{
 int left,right,largest;
 float tem;
 left = LEST(i);
 right = RIGHT(i);
 if((left <= length) && (array[left]>array[i]))
    largest = left;
 else largest = i;
 if((right<=length)&&(array[right]>array[largest]))
    largest = right;
 if (largest!=i)
 {
  tem = array[i];
  array[i] = array[largest];
  array[largest] = tem;
  max_heap(largest);
 }
 return;
}

heap::build_max_heap()
{
 for(int j=length/2;j>0;j--)
 {
  max_heap(j);
 }
}

heap::printheap()
{
 int m=1;
 int **a;
 int width = POW_2((layer-1)*2-1);
 int high = layer;
 a = new int[high][width];
 for(int i=0;i<high;i++)
	 for (int j=0;j<width;j++)
		 a[i][j]=-1;
 
 while(m<length)
 {
  if(m>=(width-1))
  {
   cout<<
  }
 }
}
