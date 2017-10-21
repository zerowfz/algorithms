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
