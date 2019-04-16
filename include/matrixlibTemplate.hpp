namespace ml{
    //constructors and destructors:

    //copy constructor:
    template<class T> template<class U>
        matrix<T> :: matrix(const matrix<U>& m){
#if MATRIXLIB_DEBUG
            std::cout << "copy constructor called" << std::endl;
#endif
            rows = m.rows;
            cols = m.cols;
            try{
                //alloc the 2d-array:
                ml_new(ptr, rows, cols);

            }catch( std::bad_alloc &ba ){
                throw ba;
            }
            int i, j;
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    ptr[i][j] = m.ptr[i][j];
                }
            }
        }

    //move constructor:
    template<class T>
        matrix<T> :: matrix(matrix&& m){
#if MATRIXLIB_DEBUG
            std::cout << "move constructor called" << std::endl;
#endif
            //copy ints:
            rows = m.rows;
            cols = m.cols;

            //copy allocation:
            ptr = m.ptr;
            m.ptr = nullptr;
        }

    //constructor:
    template<class T>
        matrix<T> :: matrix(int rows, int cols, bool identity){
#if MATRIXLIB_DEBUG
            std::cout << "normal constructor called" << std::endl;
#endif
            this->rows = rows;
            this->cols = cols;
            try{
                //allocation:
                ml_new(ptr, rows, cols);
            }catch( std::bad_alloc &ba ){
                throw ba;
            }
            //fill matrix
            if(identity){
                int i, j;
                for(i=0; i<rows; i++){
                    for(j=0; j<cols; j++){
                        ptr[i][j] = (i == j);
                    }

                }
            }
        }

    //constructor, copy matrix:
    template<class T> template<class U> 
        matrix<T> :: matrix(U** m, int rows, int cols){
            this->rows = rows;
            this->cols = cols;
            try{
                ml_new(ptr, rows, cols);
                copy(ptr, m, rows, cols);
                ml_delete(m);
                m = ptr;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }
        }

    //constructor using single value
    template<class T>
        matrix<T> :: matrix(T value, int rows, int cols){
#if MATRIXLIB_DEBUG
            std::cout << "single value constructor called" << std::endl;
#endif
            this->rows = rows;
            this->cols = cols;
            try{
                //allocation:
                ml_new(ptr, rows, cols);
            }catch( std::bad_alloc &ba ){
                throw ba;
            }
            //fill matrix
            int i, j;
            for(i=0; i<rows; i++){
                for(j=0; j<cols; j++){
                    ptr[i][j] = value;
                }
            }
    }

    //destructor:
    template<class T> 
        matrix<T> :: ~matrix(){
#if MATRIXLIB_DEBUG
            std::cout << "destructor called" << std::endl;
#endif
            //deallocation:
            ml_delete(ptr);
        }
    //-----------------------------------------------------


    //gets and sets:
    template<class T> 
        int matrix<T>::getRows(){
            return rows;
        }

    template<class T> 
        int matrix<T>::getCols(){
            return cols;
        }

    template<class T> 
        T** matrix<T>::getMatrix(){
            return ptr;
        }

    //----------------------------    

    //operators:
    //copy assignment operator:
    template<class T> template<class U> 
        matrix<T>& matrix<T>::operator= (const matrix<U> &m ){
#if MATRIXLIB_DEBUG
            std::cout << "copy assignment operator called" << std::endl;
#endif
            //check for self-assignment:
            if(((void*)&m) == ((void*)this)){
                return *this;
            }
            //if the objects are different:
            //copy m.matrix to this->matrix:
            copy(ptr, m.ptr, rows, cols);
            return *this;
        }

    //move assignment operator:
    template<class T> template<class U> 
        matrix<T>& matrix<T>::operator= (matrix<U>&& m ){
#if MATRIXLIB_DEBUG
            std::cout << "move assignment operator called" << std::endl;
#endif
            //make a manual cast:
            copy(ptr, m.ptr, rows, cols);

            return *this;
        }

    //type-cast operator:
    template<class T> template<class U>
        matrix<T> :: operator matrix<U>(){
#if MATRIXLIB_DEBUG
            std::cout << "type-cast operator called from " << typeid(T).name() << " to " << typeid(U).name() << std::endl;
#endif
            try{
                matrix<U> m(*this);

                return m;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }
        }

    //+ operator:
    template<class T>
        matrix<T> matrix<T> :: operator+(const matrix<T>& m) const{
            //alloc:
            try{
                matrix<T> m3(rows, cols);

                //sum:
                int i, j;
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        m3.ptr[i][j] = ptr[i][j] + m.ptr[i][j];
                    }
                }
                return m3;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }

        }

    //- operator:
    template<class T>
        matrix<T> matrix<T> :: operator-(const matrix<T>& m) const{
            //alloc:
            try{
                matrix<T> m3(rows, cols);

                //subtraction:
                int i, j;
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        m3.ptr[i][j] = ptr[i][j] - m.ptr[i][j];
                    }
                }
                return m3;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }

        }

    //* operator:
    template<class T>
        matrix<T> matrix<T> :: operator*(const matrix<T>& m) const{
            //alloc:
            try{
                matrix<T> m3(rows, m.cols);

                //multiplication:
                int i, j, k;
                for (i = 0; i < m3.rows; i++) {
                    for (j = 0; j < m3.cols; j++) {
                        m3.ptr[i][j] = 0;
                        for(k = 0; k < cols; k++){
                            m3.ptr[i][j] += ptr[i][k] * m.ptr[k][j];
                        }
                    }
                }
                return m3;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }

        }

    // / operator:
    template<class T>
        matrix<T> matrix<T> :: operator/(const matrix<T>& m) const{
            //alloc:
            try{
                matrix<T> m3(rows, cols);

                //division:
                int i, j;
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        m3.ptr[i][j] = ptr[i][j] / m.ptr[i][j];
                    }
                }
                return m3;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }

        }

    //returns the pointer to the row position:
    template<class T> 
        T*& matrix<T>::operator[](int position) const{
            return ptr[position];
        }

    //return a ostream of the matrix to be used in the cout call:
    template<class T> 
        std::ostream& operator<<(std::ostream &output, const matrix<T> &m){
            int eLength = 4 , eHeight = 2, ePrecision = 3;
            int i, j;
            for (i = 0; i < m.rows; i++) {
                for (j = 0; j < m.cols; j++) {
                    output << "  " << std::setw(eLength) << std::setprecision(ePrecision) << m.ptr[i][j];
                }
                if(i != m.rows-1) output << std::string(eHeight, '\n');
            }
            return output;
        }
    //-----------------------------------------------------

    //return a newly allocated transposed matrix
    template<class T>
        matrix<T> matrix<T> :: transpose() const{
            //alloc:
            try{
                matrix<T> m(rows, cols);

                //transposition:
                int i, j;
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        m.ptr[j][i] = ptr[i][j];
                    }
                }
                return m;
            }catch( std::bad_alloc &ba ){
                throw ba;
            }
        }


    //functions:

    //alloc a 2d-array:
    template<class T>
        void ml_new(T**& m, int rows, int cols){
            //allocation:
            try{
                m = new T*[rows];
                m[0] = new T[rows*cols];
            }catch( std::bad_alloc &ba ){ //if new fails
                throw ba;
            }

            //linkage:
            int i;
            for (i = 1; i < rows; i++) {
                m[i] = m[0] + i * cols;
            }
        }

    //delete matrix allocated by new:
    template<class T> 
        void ml_delete(T**& m){
            if(m)delete[] m[0]; //delete the T block
            delete[] m; //delete the pointer array
        }

    //copy 2dArray, does not work with static allocated 2d arrays:
    template<class T, class U> 
        void copy(T** &m1, U** m2, int rows, int cols){
            int i, j;
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    m1[i][j] = m2[i][j];
                }
            }
        }

    //print a 2dArray:
    template<class T> 
        void print(T** &m, int rows, int cols, int eLength, int eHeight, int ePrecision){
            int i, j;
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    std::cout << std::setw(eLength) << std::setprecision(ePrecision) << m[i][j];
                }
                std::cout << std::string(eHeight, '\n');
            }
        }



}
