#include <iostream>


#include <graphicslib.hpp>
#include <matrixlib.hpp>
#include <utils.hpp>


#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define ROWS 2
#define COLS 2


void translationTest(){
    ml::matrix<float> position(1.f, 3, 1);
    ml::matrix<float> identityMatrix(4, 4, true);

    ml::matrix<float> translationMatrix = utils::translate(identityMatrix, position);

    std::cout << "position:" << std::endl << position << std::endl;
    std::cout << "identity:" << std::endl << identityMatrix << std::endl;
    std::cout << "translation matrix:" << std::endl << translationMatrix << std::endl;
}

void rotationTest(){
    float angle = 3.1415/6.f;
    ml::matrix<float> identityMatrix(4, 4, true);

    ml::matrix<float> rotationMatrix = utils::rotateZ(identityMatrix, angle);

    std::cout << "angle:" << std::endl << angle << std::endl;
    std::cout << "identity:" << std::endl << identityMatrix << std::endl;
    std::cout << "rotation matrix:" << std::endl << rotationMatrix << std::endl;
}

void scaleTest(){
    ml::matrix<float> scale(2.f, 3, 1);
    ml::matrix<float> identityMatrix(4, 4, true);

    ml::matrix<float> scaleMatrix = utils::scale(identityMatrix, scale);

    std::cout << "scale:" << std::endl << scale << std::endl;
    std::cout << "identity:" << std::endl << identityMatrix << std::endl;
    std::cout << "scale matrix:" << std::endl << scaleMatrix << std::endl;
}


int main(int argc, char const *argv[]) {
    //translationTest();
    //scaleTest();
    //rotationTest();


    graphicslib::Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.createWindow();
    window.run();

    std::cout << "oi gentee" << std::endl;
    /*

    ml::matrix<float> m3(1.f, ROWS, COLS);
    ml::matrix<float> m4(ROWS, COLS, true);
    ml::matrix<float> m5(ROWS, COLS);
    //ml::matrix<int> m5 = ml::matrix<int>(ROWS, COLS);
    //ml::matrix<int> m6(ROWS, COLS);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            m3[i][j] = i*ROWS+j+1;
            m4[i][j] = 0.5;
            m5[i][j] = 2;
            //m6[i][j] = 2;
        }
    }

    //matrix<int> m5(m3+m4);
    m5 = m3 * m4;
    //(m3 + m4) + (m5 + m6);
    //m5 = (ml::matrix<float>)m3 + m4;
    //m3 + m4;
    //(ml::matrix<int>) m3 + m4;
    //cout << (m3 + m4) << endl;

    cout << "m3:" << endl << m3 << endl;
    cout << "m4:" << endl << m4 << endl;
    cout << "m5:" << endl << m5 << endl;
    //cout << "m6:" << endl << m6 << endl;
    */



    return 0;
}








/*
#include <iostream>
#include "../include/matrixlib.hpp"
#define ROWS 2
#define COLS 2


using namespace std;

int main(){

    ml::matrix<float> m3(ROWS, COLS);
    ml::matrix<float> m4(ROWS, COLS);
    ml::matrix<float> m5(ROWS, COLS);
    //matrix<int> m5 = matrix<int>(ROWS, COLS);
    //matrix<int> m6(ROWS, COLS);
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            m3[i][j] = i*ROWS+j+1;
            m4[i][j] = 0.5;
            m5[i][j] = 2;
            //m6[i][j] = 2;
        }
    }
    
    //matrix<int> m5(m3+m4);
    m5 = m3 + m4;
    //(m3 + m4) + (m5 + m6);
    //m5 = (ml::matrix<float>)m3 + m4;
    //m3 + m4;
    //(ml::matrix<int>) m3 + m4;
    //cout << (m3 + m4) << endl;

    cout << "m3:" << endl << m3 << endl;
    cout << "m4:" << endl << m4 << endl;
    cout << "m5:" << endl << m5 << endl;
    //cout << "m6:" << endl << m6 << endl;

    return 0;
}


*/
