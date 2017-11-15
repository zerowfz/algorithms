#include "sort.h"
#include "heap.hpp"
int main()
{
 float a[]={1,2,3,7,4,3};
 InsertSort sort(a,6);
 sort.process();
 sort.output();
 MergeSort msort(a,6);
 msort.process();
 msort.output();
 heap s(a,6);
 s.build_max_heap();
 s.printheap();
}
