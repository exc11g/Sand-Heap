#pragma once

#include <malloc.h>
#include <cstdio>
#include <fstream>
#include <array>

#ifndef BIN_BMP_H
#define BIN_BMP_H

static const uint8_t kSizeOfFileHeader = 14;
static const uint8_t kSizeOfInfoHeader = 40;
static const uint8_t kSizeOfColorTable = 20;

struct MyImage {
    //uint16_t length;
    //uint16_t width;
    char* fileName;

    MyImage(const uint16_t& len, const uint16_t& wid, uint64_t** array, char* name) {
        fileName = name;
        completion(array, len, wid);
    }

    void completion(uint64_t** array, const uint32_t length, const uint32_t width) {

        uint32_t sizeOfPadding = (4 - (width % 4)) % 4;
        uint32_t sizeOfFile = kSizeOfFileHeader + kSizeOfInfoHeader + length * (width + sizeOfPadding) + kSizeOfColorTable;
        std::ofstream imageFile;
        imageFile.open(fileName);

        std::array<unsigned char, kSizeOfFileHeader> fileHeader = InitFileHeader(length, sizeOfFile);
        std::array<unsigned char, kSizeOfInfoHeader> infoHeader = InitInfoHeader(length, width);
        std::array<unsigned char, kSizeOfColorTable> colorTable = InitColorTable();

        unsigned char padding[] = {0, 0, 0};

        imageFile.write(reinterpret_cast<char*>(fileHeader.begin()), kSizeOfFileHeader);
        imageFile.write(reinterpret_cast<char*>(infoHeader.begin()), kSizeOfInfoHeader);
        imageFile.write(reinterpret_cast<char*>(colorTable.begin()), kSizeOfColorTable);

        for (uint16_t i = 0; i < length; ++i) {
            for (uint16_t j = 0; j < width; ++j) {
                if (array[i][j] < 4) {
                    imageFile << (uint8_t) array[i][j];
                } else {
                    imageFile << (uint8_t) 4;
                }
            }
            imageFile.write(reinterpret_cast<char*>(padding), sizeOfPadding);
        }

        imageFile.close();
    }

    std::array<unsigned char, kSizeOfColorTable> InitColorTable() {
        std::array<unsigned char, kSizeOfColorTable> colorTable {0};

        colorTable[0] = 255;
        colorTable[1] = 255;
        colorTable[2] = 255;
        colorTable[3] = 1;

        colorTable[4] = 0;
        colorTable[5] = 255;
        colorTable[6] = 0;
        colorTable[7] = 1;

        colorTable[8] = 255;
        colorTable[9] = 0;
        colorTable[10] = 139;
        colorTable[11] = 1;

        colorTable[12] = 0;
        colorTable[13] = 255;
        colorTable[14] = 255;
        colorTable[15] = 1;

        colorTable[16] = 0;
        colorTable[17] = 0;
        colorTable[18] = 0;
        colorTable[19] = 1;

        return colorTable;
    }

    std::array<unsigned char, kSizeOfInfoHeader> InitInfoHeader(const uint16_t length, uint16_t width) {
        std::array<unsigned char, kSizeOfInfoHeader> infoHeader {0};
        infoHeader[0] = kSizeOfInfoHeader;

        infoHeader[4] = width;
        infoHeader[5] = width >> 8;
        infoHeader[6] = width >> 16;
        infoHeader[7] = width >> 24;

        infoHeader[8] = length;
        infoHeader[9] = length >> 8;
        infoHeader[10] = length >> 16;
        infoHeader[11] = length >> 24;

        infoHeader[12] = 1;
        infoHeader[14] = 8;
        infoHeader[32] = 5;

        return infoHeader;
    }

    std::array<unsigned char, kSizeOfFileHeader> InitFileHeader(const uint16_t& len, const uint32_t& sizeOfFile) {
        std::array<unsigned char, kSizeOfFileHeader> fileHeader {0};
        fileHeader[0] = 'B';
        fileHeader[1] = 'M';

        fileHeader[2] = sizeOfFile;
        fileHeader[3] = sizeOfFile >> 8;
        fileHeader[4] = sizeOfFile >> 16;
        fileHeader[5] = sizeOfFile >> 24;

        fileHeader[10] = (kSizeOfInfoHeader + kSizeOfColorTable + kSizeOfFileHeader);
        fileHeader[11] = (kSizeOfInfoHeader + kSizeOfColorTable + kSizeOfFileHeader) >> 8;
        fileHeader[12] = (kSizeOfInfoHeader + kSizeOfColorTable + kSizeOfFileHeader) >> 16;
        fileHeader[13] = (kSizeOfInfoHeader + kSizeOfColorTable + kSizeOfFileHeader) >> 24;

        return fileHeader;
    }

};

#endif //BIN_BMP_H
