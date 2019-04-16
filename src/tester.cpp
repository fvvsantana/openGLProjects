#include <utils.hpp>
#include <matrixlib.hpp>

namespace tester {

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
}
