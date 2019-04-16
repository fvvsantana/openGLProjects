#include <utils.hpp>
#include <string>
#include <fstream>
#include <cmath>

#include <matrixlib.hpp>

namespace utils{
    //copy file content to outputString
    bool fileToString(char* filePath, std::string &outputString){
        std::ifstream inFile;
        std::string temp = "";

        //open file
        inFile.open(filePath);

        //check if the file is open
        if(!inFile.is_open()){
            //failure
            return false;
        }

        //copy the file to outputString
        while(std::getline(inFile, temp)){
            outputString.append(temp + "\n");
        }

        //close the file
        inFile.close();

        //success
        return true;
    }

    //apply a translation operation over the model matrix
    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, ml::matrix<float> &position){
        int n = position.getRows() + 1;
        ml::matrix<float> translationMatrix(n, n, true);
        int i;
        for(i=0; i<n-1; i++){
            translationMatrix[i][n-1] = position[i][0];
        }

        return modelMatrix * translationMatrix;
    }

    ml::matrix<float> rotateZ(ml::matrix<float> &modelMatrix, float angle){
        ml::matrix<float> rotationMatrix(4, 4, true);
        rotationMatrix[0][0] = cos(angle);
        rotationMatrix[0][1] = (-1) * sin(angle);
        rotationMatrix[1][0] = sin(angle);
        rotationMatrix[1][1] = cos(angle);

        return modelMatrix * rotationMatrix;
    }

    ml::matrix<float> scale(ml::matrix<float> &modelMatrix, ml::matrix<float> &scale){
        int n = scale.getRows() + 1;
        ml::matrix<float> scaleMatrix(n, n, true);
        int i;
        for(i=0; i<n-1; i++){
            scaleMatrix[i][i] = scale[i][0];
        }

        return modelMatrix * scaleMatrix;
    }


}
