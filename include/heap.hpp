#ifndef HEAP_H
#define HEAP_H
class print_buf
{
    public:
        int buf_x;
        const int width;
        const int height;
        float* buf;
        
        print_buf()
           :width(128),height(6),buf_x(0){ buf = new float[width*height];}      
};

class heap{
    public:
        float* array;
        int length;
        int layer;
        /*
		inline int get_layer(int n)
		{
			 int layer=0;
			 int x=1;
			 while(n>=x)
			 {
			  x *=2;
			  layer++;
			 }
			 return layer;
		};*/
		heap(float *A,int n);/*
        heap(float *A,int n)
		:array(A),length(n){layer = get_layer(n);};*///内联函数必须在使用之前先定义好 
        void build_max_heap();
        void printheap();
	//int push();
	//int extend();

    private:
        inline int PARENT(int i){return i/2;}
        inline int LEFT(int i){return 2*i;}
        inline int RIGHT(int i){return 2*i+1;}
        inline int get_layer(int n);
		void max_heap(int i);
		void print_(int,int);
		print_buf tem;
	
};
#endif
