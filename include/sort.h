#ifndef __SORT_H
#define __SORT_H
#include <iostream>
#include "heap.h"
extern const float MAX;
using namespace std;
class sortbase
{
 public:
	 const float *const ls_;
	 const int num_array;
	 float *ls_done;
         sortbase(float *A,int N);
	 virtual void process()=0;
	 void output(){for(int i=0;i<num_array;i++)cout<<ls_done[i]<<" ";cout<<endl;}
};

class InsertSort:public sortbase
{
 public:
	 explicit InsertSort(float* A,int N)
		 :sortbase(A,N){}
	 void process(){insert();}
 private:
	 void insert();

	
};

class MergeSort:public sortbase
{
 public:
	 explicit MergeSort(float* A,int N)
		 :sortbase(A,N){}
	 void process(){sort(ls_done,0,num_array-1);}
 private:
	 void sort(float* A,int s,int f);
	 void merge(float* A,int s,int m,int f);
};

class HeapSort:public sortbase
{
 public:
	 explicit HeapSort(float* A,int N)
		 :sortbase(A,N),heap_(ls_done,N){}
         void process();       
 private:
	 heap heap_;
};

class QuickSort:public sortbase
{
 public:
	 explicit QuickSort(float* A,int N)
		 :sortbase(A,N){}
	 void process(){quicksort(ls_done,0,num_array-1);}
	 void quicksort(float*,int,int);
	 int patition(float*,int,int);
};
#endif

