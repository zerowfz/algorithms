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
        heap(float *A,int n)
		:array(A),length(n){layer = get_layer(n);};
        void build_max_heap();
        void printheap();
	//int push();
	//int extend();

    private:
        inline int PARENT(int i){return i/2;}
        inline int LEFT(int i){return 2*i;}
        inline int RIGHT(int i){return 2*i+1;}
        //inline int get_layer(int n); 
        inline int get_layer(int n)//内联函数定义,可放在调用之前或之后 
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
		void max_heap(int i);
		void print_(int,int);
		print_buf tem;
	
};
#endif
