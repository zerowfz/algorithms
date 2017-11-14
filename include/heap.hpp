
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
	
}
