#include <utils.hpp>
#include <matrixlib.hpp>

namespace tester {

    //do the same operations that are executed in the run function, but without transposition
    void matrixOperationsTest(){
        ml::matrix<float> position(3, 1);
        position[0][0] = 1;
        position[1][0] = 2;
        position[2][0] = 3;
        float angle = 3.1415/6.f;
        ml::matrix<float> scale(1.f, 3, 1);

        ml::matrix<float> modelMatrix(4, 4, true);
        modelMatrix = utils::translate(modelMatrix, position);
        modelMatrix = utils::rotateZ(modelMatrix, angle);
        modelMatrix = utils::scale(modelMatrix, scale);

        std::cout << "modelMatrix:\n" << modelMatrix << std::endl;
    }

    //test translation
    void translationTest(){
        ml::matrix<float> position(3, 1);
        position[0][0] = 1;
        position[1][0] = 2;
        position[2][0] = 3;
        ml::matrix<float> identityMatrix(4, 4, true);

        ml::matrix<float> translationMatrix = utils::translate(identityMatrix, position);

        std::cout << "position:" << std::endl << position << std::endl;
        std::cout << "identity:" << std::endl << identityMatrix << std::endl;
        std::cout << "translation matrix:" << std::endl << translationMatrix << std::endl;
    }

    //test rotation
    void rotationTest(){
        float angle = 3.1415/6.f;
        ml::matrix<float> identityMatrix(4, 4, true);

        ml::matrix<float> rotationMatrix = utils::rotateZ(identityMatrix, angle);

        std::cout << "angle:" << std::endl << angle << std::endl;
        std::cout << "identity:" << std::endl << identityMatrix << std::endl;
        std::cout << "rotation matrix:" << std::endl << rotationMatrix << std::endl;
    }

    //test scale
    void scaleTest(){
        ml::matrix<float> scale(2.f, 3, 1);
        ml::matrix<float> identityMatrix(4, 4, true);

        ml::matrix<float> scaleMatrix = utils::scale(identityMatrix, scale);

        std::cout << "scale:" << std::endl << scale << std::endl;
        std::cout << "identity:" << std::endl << identityMatrix << std::endl;
        std::cout << "scale matrix:" << std::endl << scaleMatrix << std::endl;
    }
}
