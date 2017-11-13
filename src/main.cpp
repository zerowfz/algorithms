/*
<<<<<<< HEAD:src/main.cpp
#include "sort.hpp"
int main()
{
 float a[]={1,2,3,7,4,3};
 InsertSort sort(a,6);
 sort.process();
 sort.output();
}
=======*/
#include "sort.hpp"
#include "heap.hpp"
int main()
{
 float a[]={1.56,-2,13,-7,24.67,-3.46};
 InsertSort sort(a,6);
 sort.process();
 sort.output();
 MergeSort msort(a,6);
 msort.process();
 msort.output();
 heap heap_(a,6);
 heap_.build_max_heap();
 heap_.printheap();//运行结果很奇怪 
}
//>>>>>>> wfz2/dev:src/test.cpp


