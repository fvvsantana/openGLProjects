#include <iostream>


#include <graphicslib.hpp>
#include <matrixlib.hpp>
#include <utils.hpp>


#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define ROWS 2
#define COLS 2

using namespace std;

void translationTest(){
    ml::matrix<float> position(1.f, 3, 1);
    ml::matrix<float> identityMatrix(4, 4, true);

    ml::matrix<float> translationMatrix = utils::translate(identityMatrix, position);

    cout << "position:" << endl << position << endl;
    cout << "identity:" << endl << identityMatrix << endl;
    cout << "translation matrix:" << endl << translationMatrix << endl;
}

void rotationTest(){
    float angle = 3.1415/6.f;
    ml::matrix<float> identityMatrix(4, 4, true);

    ml::matrix<float> rotationMatrix = utils::rotateZ(identityMatrix, angle);

    cout << "angle:" << endl << angle << endl;
    cout << "identity:" << endl << identityMatrix << endl;
    cout << "rotation matrix:" << endl << rotationMatrix << endl;
}

void scaleTest(){
    ml::matrix<float> scale(2.f, 3, 1);
    ml::matrix<float> identityMatrix(4, 4, true);

    ml::matrix<float> scaleMatrix = utils::scale(identityMatrix, scale);

    cout << "scale:" << endl << scale << endl;
    cout << "identity:" << endl << identityMatrix << endl;
    cout << "scale matrix:" << endl << scaleMatrix << endl;
}


int main(int argc, char const *argv[]) {
    //translationTest();
    //scaleTest();
    //rotationTest();


    graphicslib::Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.createWindow();
    window.run();

    cout << "oi gentee" << endl;
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
    //texture init

    //texture 0
    int image_width = 0;
    int image_height = 0;
    unsigned char* image = SOIL_load_image("resources/textures/assembla.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cerr << "ERROR::TEXTURE_LOADING_FAILED" << std::endl;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    //texture 1
    int image_width1 = 0;
    int image_height1 = 0;
    unsigned char* image1 = SOIL_load_image("resources/textures/img_test.png", &image_width1, &image_height1, NULL, SOIL_LOAD_RGBA);

    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(image1){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cerr << "ERROR::TEXTURE_LOADING_FAILED" << std::endl;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image1);

    */



    //delete vao and buffers

















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
