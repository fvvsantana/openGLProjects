#include <utils.hpp>
#include <string>
#include<fstream>

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


}
