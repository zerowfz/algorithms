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
		:array(A),length(n),layer(get_layer(n)){};
        void build_max_heap();
        void printheap();
	int push();
	int extend();

    private:
        inline int PARENT(int i){return i/2;}
        inline int LEFT(int i){return 2*i;}
        inline int RIGHT(int i){return 2*i+1;}
	void max_heap(int i);
	inline int get_layer(int);
	void print_(int,int);
	print_buf tem;
	
};



