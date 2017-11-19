#include "sort.h"
int main()
{
 float a[]={1,2,3,7,4,3};
 InsertSort sort(a,6);
 sort.process();
 sort.output();
 MergeSort msort(a,6);
 msort.process();
 msort.output();
 HeapSort hsort(a,6);
 hsort.process();
 hsort.output();
 QuickSort qsort(a,6);
 //for (int i=0;i<6;i++)cout<<qsort.ls_done[i]<<endl;
 qsort.process();
 qsort.output();
}
