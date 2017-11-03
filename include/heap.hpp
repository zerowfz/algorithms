
class heap{
    public:
        float* array;
        int length;
        int layer=0;
        heap(float *A,int n);
        inline int PARENT(int i){return i/2;}
        inline int LEFT(int i){return 2*i;}
        inline int RIGHT(int i){return 2*i+1;}
        void max_heap(int i);
        void build_max_heap();
        void printheap();
}
