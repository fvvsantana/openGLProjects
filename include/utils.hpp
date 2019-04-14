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
    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, ml::matrix<float> &position);
    ml::matrix<float> rotateZ(ml::matrix<float> &modelMatrix, float angle);
    ml::matrix<float> scale(ml::matrix<float> &modelMatrix, ml::matrix<float> &scale);

}

#endif
