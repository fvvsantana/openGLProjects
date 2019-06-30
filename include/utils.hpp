#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace ml{
    template<class T>
        class matrix;
}

namespace utils{
    //copy file content to outputString
    bool fileToString(char* filePath, std::string &outputString);
    //apply translation in the model matrix
    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, float* position);
    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, ml::matrix<float> &position);
    //apply rotation around X axis in the model matrix
    ml::matrix<float> rotateX(ml::matrix<float> &modelMatrix, float angle);
    //apply rotation around Y axis in the model matrix
    ml::matrix<float> rotateY(ml::matrix<float> &modelMatrix, float angle);
    //apply rotation around Z in the model matrix
    ml::matrix<float> rotateZ(ml::matrix<float> &modelMatrix, float angle);
    //apply scale in the model matrix
    ml::matrix<float> scale(ml::matrix<float> &modelMatrix, float* scale);
    ml::matrix<float> scale(ml::matrix<float> &modelMatrix, ml::matrix<float> &scale);
    //return the orthogonal projection's matrix
    ml::matrix<float> orthogonalMatrix(float xw_max, float xw_min, float yw_max, float yw_min, float z_near, float z_far);
    //return the perspective projection's matrix
    ml::matrix<float> perspectiveMatrix(float left, float right, float bottom, float top, float near, float far);
}

#endif
