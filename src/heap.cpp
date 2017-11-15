#include "heap.hpp"
#include <iostream>
using namespace std;
const float INF_=-999.99;
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

void heap::max_heap(int i)
{
 int left,right,largest;
 float tem;
 left = LEFT(i);
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

void heap::build_max_heap()
{
 for(int j=length/2;j>0;j--)
 {
  max_heap(j);
 }
}
/*该函数的目的在于可视化一个堆的结构，
首先定义一个二维数组记录每个节点的位置，即如果该位置
有值则附该节点的值，否则都是INF，然后利用树的中序遍历，
这样每次都可以得到*/
void heap::printheap()
{
 n = tem.width*tem.height;
 for(int i=0;i<n;i++)
     tem.buf[i]=INF_;
 print_(1,1);
 for(int i=0;i<n;i++)
 {
     if(tem.buf[i]==INF_)
     cout<<" ";
     else cout<<buf[i][j];
     if((i+1)%tem.width==0)cout<<endl;
  }
 }
}

void heap::print_(int base,int l)
{

 if (base>length)
 {
  tem.buf_x += POW_2(layer-l)-1;
  return;
 }
 print_(2*base,l+1);
 int id = (l-1)*tem.width+ tem.buf_x;
 buf[id] = array[base-1];
 print_(2*base+1,l+1);
}
