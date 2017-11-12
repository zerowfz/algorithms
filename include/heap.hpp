class print_buf;
class heap{
    public:
        float* array;
        int length;
        int layer;
        heap(float *A,int n);
        inline int PARENT(int i){return i/2;}
        inline int LEFT(int i){return 2*i;}
        inline int RIGHT(int i){return 2*i+1;}
        void max_heap(int i);
        void build_max_heap();
        void printheap();
        void print_(int,int);
        print_buf tem;
        
};
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

