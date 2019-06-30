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

    //apply translation in the model matrix
    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, float* position){
        int n = 4;
        ml::matrix<float> translationMatrix(n, n, true);
        int i;
        for(i=0; i<n-1; i++){
            translationMatrix[i][n-1] = position[i];
        }

        return modelMatrix * translationMatrix;
    }

    ml::matrix<float> translate(ml::matrix<float> &modelMatrix, ml::matrix<float> &position){
        int n = position.getRows() + 1;
        ml::matrix<float> translationMatrix(n, n, true);
        int i;
        for(i=0; i<n-1; i++){
            translationMatrix[i][n-1] = position[i][0];
        }

        return modelMatrix * translationMatrix;
    }

    //apply rotation around Z axis in the model matrix
    ml::matrix<float> rotateZ(ml::matrix<float> &modelMatrix, float angle){
        ml::matrix<float> rotationMatrix(4, 4, true);
        rotationMatrix[0][0] = cos(angle);
        rotationMatrix[0][1] = (-1) * sin(angle);
        rotationMatrix[1][0] = sin(angle);
        rotationMatrix[1][1] = cos(angle);

        return modelMatrix * rotationMatrix;
    }

    //apply rotation around X axis in the model matrix
    ml::matrix<float> rotateX(ml::matrix<float> &modelMatrix, float angle){
        ml::matrix<float> rotationMatrix(4, 4, true);
        rotationMatrix[1][1] = cos(angle);
        rotationMatrix[1][2] = (-1) * sin(angle);
        rotationMatrix[2][1] = sin(angle);
        rotationMatrix[2][2] = cos(angle);

        return modelMatrix * rotationMatrix;
    }

    //apply rotation around Y axis in the model matrix
    ml::matrix<float> rotateY(ml::matrix<float> &modelMatrix, float angle){
        ml::matrix<float> rotationMatrix(4, 4, true);
        rotationMatrix[0][0] = cos(angle);
        rotationMatrix[2][0] = (-1) * sin(angle);
        rotationMatrix[0][2] = sin(angle);
        rotationMatrix[2][2] = cos(angle);

        return modelMatrix * rotationMatrix;
    }
    //apply scale in the model matrix
    ml::matrix<float> scale(ml::matrix<float> &modelMatrix, float* scale){
        int n = 4;
        ml::matrix<float> scaleMatrix(n, n, true);
        int i;
        for(i=0; i<n-1; i++){
            scaleMatrix[i][i] = scale[i];
        }

        return modelMatrix * scaleMatrix;
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

    ml::matrix<float> orthogonalMatrix(float xw_max, float xw_min, float yw_max, float yw_min, float z_near, float z_far){
        ml::matrix<float> orthogonal(4, 4, true);

        orthogonal[0][0] = 2.f/(xw_max-xw_min);
        orthogonal[0][3] = -(xw_max+xw_min)/(xw_max-xw_min);
        orthogonal[1][1] = 2.f/(yw_max-yw_min);
        orthogonal[1][3] = -(yw_max+yw_min)/(yw_max-yw_min);
        orthogonal[2][2] = -2.f/(z_near-z_far);
        orthogonal[2][3] = (z_near+z_far)/(z_near-z_far);

        return orthogonal;
    }

    ml::matrix<float> perspectiveMatrix(float left, float right, float bottom, float top, float near, float far){
        ml::matrix<float> perspective(0.f, 4, 4);

        perspective[0][0] = (2.f*near)/(right-left);
        perspective[0][2] = (right+left)/(right-left);
        perspective[1][1] = (2.f*near)/(top-bottom);
        perspective[1][2] = (top+bottom)/(top-bottom);
        perspective[2][2] = -(near+far)/(far-near);
        perspective[2][3] = (-2.f*near*far)/(far-near);
        perspective[3][2] = -1.f;

        return perspective;
    }
}
