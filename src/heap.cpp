#include "heap.h"
#include <iostream>
using namespace std;
const float INF_=-999.99;
inline int POW_2(int n){ int x=1;while(n>0){x*=2;n--;}return x;}

int heap::get_layer(int n)
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
 if((left <= length) && (array[left-1]>array[i-1]))
    largest = left;
 else largest = i;
 if((right<=length)&&(array[right-1]>array[largest-1]))
    largest = right;
 if (largest!=i)
 {
  tem = array[i-1];
  array[i-1] = array[largest-1];
  array[largest-1] = tem;
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
 int n = tem.width*tem.height;
 for(int i=0;i<n;i++)
     tem.buf[i]=INF_;
 print_(1,1);
 for(int i=0;i<n;i++)
 {
     if(tem.buf[i]==INF_)
     cout<<" ";
     else cout<<tem.buf[i];
     if((i+1)%tem.width==0)cout<<endl;
 }
 
}

void heap::print_(int base,int l)
{

 if (base>length)
 {
  tem.buf_x += POW_2(layer-l)-1;
  return;
 }
 print_(LEFT(base),l+1);
 tem.buf_x++;
 int id = (l-1)*tem.width+ tem.buf_x;
 tem.buf[id] = array[base-1];
 print_(RIGHT(base),l+1);
}

int heap::push()
{
 length--;
 layer = get_layer(length);
 //把
 float out = array[0];
 array[0]=array[length];
 max_heap(1);
 return out;
}
/*
// 测试程序：
int main()
{
 float a[]={1,2,3,7,5,4};
 heap s(a,6);
 s.build_max_heap();
 for(int i=0;i<6;i++)
	 cout<<s.array[i]<<endl;
 s.printheap();
}
*/
