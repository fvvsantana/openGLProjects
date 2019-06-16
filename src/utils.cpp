#include <utils.hpp>
#include <string>
#include <fstream>
#include <cmath>

#include <matrixlib.hpp>

// orthographic box
#define XW_MIN -1.5f
#define XW_MAX 1.5f
#define YW_MIN -1.5f
#define YW_MAX 1.5f
#define Zo_NEAR 5.f
#define Zo_FAR -5.f

// perspective frustum
#define RIGHT 1.f
#define LEFT 0.f
#define TOP 1.f
#define BOTTOM 0.f
#define Zp_NEAR 5.f
#define Zp_FAR -5.f

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

    ml::matrix<float> orthogonalMatrix(){
        ml::matrix<float> orthogonal(4, 4, true);

        orthogonal[0][0] = 2.f/(XW_MAX-XW_MIN);
        orthogonal[0][3] = -(XW_MAX+XW_MIN)/(XW_MAX-XW_MIN);
        orthogonal[1][1] = 2.f/(YW_MAX-YW_MIN);
        orthogonal[1][3] = -(YW_MAX+YW_MIN)/(YW_MAX-YW_MIN);
        orthogonal[2][2] = -2.f/(Zo_NEAR-Zo_FAR);
        orthogonal[2][3] = (Zo_NEAR+Zo_FAR)/(Zo_NEAR-Zo_FAR);

        return orthogonal;
    }

    ml::matrix<float> perspectiveMatrix(){
        ml::matrix<float> perspective(0.f, 4, 4);

        perspective[0][0] = (2.f*Zp_NEAR)/(RIGHT-LEFT);
        perspective[0][2] = (RIGHT+LEFT)/(RIGHT-LEFT);
        perspective[1][1] = (2.f*Zp_NEAR)/(TOP-BOTTOM);
        perspective[1][2] = (TOP+BOTTOM)/(TOP-BOTTOM);
        perspective[2][2] = -(Zp_NEAR+Zp_FAR)/(Zp_FAR-Zp_NEAR);
        perspective[2][3] = (-2.f*Zp_NEAR*Zp_FAR)/(Zp_FAR-Zp_NEAR);
        perspective[3][2] = -1.f;

        return perspective;
    }
}
