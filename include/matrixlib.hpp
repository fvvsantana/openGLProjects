#ifndef MATRIXLIB_HPP
#define MATRIXLIB_HPP
#define MATRIXLIB_DEBUG 0

#include <iostream>
#include <string>
#include <typeinfo>
#include <iomanip>
#include <new>
#include <stdexcept>

namespace ml{
    template<class T> 
        class matrix;

    template<class T>
        std::ostream& operator<<(std::ostream &output, const matrix<T> &m);


    template<class T>
        class matrix{
            private:
                int rows, cols;
                T** ptr;

            public:
                //makes all instantiations of this class template friend of each other:
                template<class U>
                    friend class matrix;
                //----------------------------

                //constructors and destructors:
                //copy constructor:
                template<class U>
                    matrix(const matrix<U>& m);

                //move constructor:
                matrix(matrix&& m);

                //constructor:
                matrix(int rows, int cols, bool identity = false);

                //constructor, copy matrix:
                template<class U> 
                    matrix(U** m, int rows, int cols);

                //constructor using single value
                matrix(T value, int rows, int cols);

                //destructor:
                ~matrix();
                //----------------------------

                //gets and sets:
                int getRows();
                int getCols();
                T** getMatrix();
                //----------------------------    

                //operators:
                //copy assignment operator:
                template<class U> 
                    matrix& operator= (const matrix<U> &m);

                //move assignment operator:
                template<class U> 
                    matrix& operator= (matrix<U> &&m);

                //type-cast operator:
                template<class U>
                    operator matrix<U>();

                //+ operator:
                matrix<T> operator+(const matrix<T>& m) const;

                //- operator:
                matrix<T> operator-(const matrix<T>& m) const;

                //* operator:
                matrix<T> operator*(const matrix<T>& m) const;

                // / operator:
                matrix<T> operator/(const matrix<T>& m) const;

                //returns the pointer to the row position:
                T*& operator[](int position) const;

                //extraction operator:
                friend std::ostream& operator<< <T>(std::ostream &output, const matrix &m);
                //----------------------------

                matrix<T> transpose() const;

        };

    //-----------------------------------------------------

    //functions:

    //alloc a 2d-array:
    template<class T>
        void ml_new(T**& m, int rows, int cols);

    //delete matrix allocated by new:
    template<class T> 
        void ml_delete(T**& m);

    //copy 2dArray:
    template<class T, class U> 
        void copy(T** &m1, U** m2, int rows, int cols);

    //print a 2dArray:
    template<class T> 
        void print(T** &m, int rows, int cols, int eLength = 4, int eHeight = 2, int ePrecision = 3);
}


// template implementations:
#include "matrixlibTemplate.hpp"

#endif /* end of include guard: MATRIXLIB_HPP */
