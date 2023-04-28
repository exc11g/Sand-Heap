#include "array.h"
#include "bmp.h"
#include "parser.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <charconv>

char* CreateWay(const char* directory, const char* name, uint64_t num, const char* format) {
    std::string stringOfNum = std::to_string(num);
    uint64_t lenOfRes = strlen(directory) + strlen(name) + stringOfNum.length() + strlen(format);
    const char* numOfPicture = stringOfNum.c_str();
    char* res = new char[lenOfRes];
    strcpy(res, directory);
    strcat(res, name);
    strcat(res, numOfPicture);
    strcat(res, format);

    return res;
}

void HandleOfArray(Array& array, Parser& parser) {
    bool valid = false;
    uint64_t iterations = 0;
    uint64_t number = 0;
    while (!valid) {
        valid = true;
        for (uint16_t i = 0; i < array.length; ++i) {
            for (uint16_t j = 0; j < array.width; ++j) {
                if (array.get(i, j) > 3) {
                    iterations++;
                    if (iterations == parser.maxIter) {

                        return;
                    }
                    if (parser.freq != 0 && (iterations % parser.freq == 0)) {
                        ++number;
                        char* fullWay = CreateWay(parser.directory, "picture_", number, ".bmp");
                        MyImage myImage(array.length, array.width,
                                        array.getArray(), fullWay);
                        delete fullWay;
                    }
                    valid = false;
                    array.dispersion(i, j);
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    Parser parser(argc, argv);

    Array array(parser.length, parser.width);

    std::ifstream fileInput;
    fileInput.open(parser.fileNameInput, std::ios::in);

    uint16_t x;
    uint16_t y;
    uint64_t value;
    while (fileInput >> x >> y >> value) {
        array.set(y - 1, x - 1, value);
    }

    HandleOfArray(array, parser);

    if (parser.freq == 0) {
        char* fullWay = CreateWay(parser.directory, "picture_", 1, ".bmp");
        MyImage myImage(array.length, array.width,
                        array.getArray(), fullWay);
        delete fullWay;
    }

    return 0;
}
