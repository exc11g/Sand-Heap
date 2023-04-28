#pragma once

#include <string>

#ifndef BIN_PARSER_H
#define BIN_PARSER_H

struct Parser {
    uint16_t length;
    uint16_t width;
    char* fileNameInput;
    char* directory;
    long long maxIter = -1;
    uint64_t freq = 0;

    Parser(int argc, char** argv) {
        for (int i = 0; i < argc; ++i) {
            if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--length") == 0) {
                length = std::stoi(argv[i + 1]);
                ++i;

            } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
                width = std::stoi(argv[i + 1]);
                ++i;

            } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--max-iter") == 0) {
                maxIter = std::stoi(argv[i + 1]);
                ++i;

            } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--freq") == 0) {
                freq = std::stoi(argv[i + 1]);
                ++i;

            } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                fileNameInput = argv[i + 1];

            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                directory = argv[i + 1];
            }
        }
    }
};

#endif //BIN_PARSER_H
