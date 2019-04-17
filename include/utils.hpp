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
    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, ml::matrix<float> &position);
    //apply rotation in the model matrix
    ml::matrix<float> rotateZ(ml::matrix<float> &modelMatrix, float angle);
    //apply scale in the model matrix
    ml::matrix<float> scale(ml::matrix<float> &modelMatrix, ml::matrix<float> &scale);

}

#endif
