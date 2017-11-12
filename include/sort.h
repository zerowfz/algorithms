<<<<<<< HEAD:include/sort.h
#include <iostream>

using namespace std;
class sortbase
{
 public:
	 float *ls_;
	 int num_array;
	 float *ls_done;
	 sortbase(float *A,int N);
	 virtual void process()=0;
	 void output(){for(int i=0;i<num_array;i++)cout<<ls_done[i]<<" ";}
};

class InsertSort:public sortbase
{
 public:
	 explicit InsertSort(float* A,int N)
		 :sortbase(A,N){}
	 void process(){insert(ls_done);}
	 void insert(float*ls);
};
=======
#include <iostream>

using namespace std;
class sortbase
{
 public:
	 float *ls_;
	 int num_array;
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
	 void process(){insert(ls_done);}
	 void insert(float*ls);

	
};

class MergeSort:public sortbase
{
 public:
	 explicit MergeSort(float* A,int N)
		 :sortbase(A,N){}
	 void process(){sort(ls_done,0,num_array-1);}
	 void sort(float* A,int s,int f);
	 void merge(float* A,int s,int m,int f);
};
>>>>>>> wfz2/dev:include/sort.hpp
