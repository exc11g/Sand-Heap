#pragma once
#include <cinttypes>
#include <iostream>
#include <cmath>
#include <malloc.h>
#include <cstdlib>
#include <cstring>

#ifndef BIN_ARRAY_H
#define BIN_ARRAY_H

struct Array {
    uint16_t length;
    uint16_t width;
    uint64_t** a = init(length, width);

    Array(uint16_t len, uint16_t wid) {
        length = len;
        width = wid;
    }

    uint64_t** init(const uint16_t& len, const uint16_t& wid) {
        uint64_t** a = (uint64_t**) malloc(sizeof(uint64_t*) * len);
        for (uint16_t i = 0; i < len; ++i) {
            a[i] = (uint64_t*) malloc(sizeof(uint64_t) * wid);
        }

        for (uint16_t i = 0; i < len; ++i) {
            for (uint16_t j = 0; j < wid; ++j) {
                a[i][j] = 0;
            }
        }

        return a;
    }

    void set(const uint16_t &i, const uint16_t &j, const uint64_t &value) {
        a[i][j] = value;
    }

    void dispersion(const int &i, const int &j) {
        uint16_t tmpLen = length;
        int flag = 0;
        add(i, j, -4);
        add(i + 1, j, 1);
        if (tmpLen != length) {
            flag = 1;
        }
        add(i - 1, j, 1);
        if (tmpLen != length && flag == 0) {
            flag = -1;
        }
        if (tmpLen != length) {
            if (flag == 1) {
                add(i, j + 1, 1);
                add(i, j - 1, 1);
            } else {
                add(i + 1, j + 1, 1);
                add(i + 1, j - 1, 1);
            }

        } else {
            add(i, j + 1, 1);
            add(i, j - 1, 1);
        }
    }

    bool add(const int i, const int j, const uint64_t value) {
        uint8_t deltaY = 0;
        uint8_t deltaX = 0;
        uint8_t deltaLen = 0;
        uint8_t deltaWid = 0;
        if (i == length) {
            deltaY = 0;
            deltaLen = 1;

        } else if (i == -1) {
            deltaY = 1;
            deltaLen = 1;

        } else if (j == width) {
            deltaX = 0;
            deltaWid = 1;

        } else if (j == -1) {
            deltaX = 1;
            deltaWid = 1;

        } else {
            a[i][j] += value;

            return true;
        }
        uint64_t** tmp = init(length + deltaLen, width + deltaWid);
        for (uint16_t y = 0; y < length; ++y) {
            for (uint16_t x = 0; x < width; ++x) {
                tmp[y + deltaY][x + deltaX] = a[y][x];
            }
        }
        deleteArray(a, length);
        a = tmp;
        a[i + deltaY][j + deltaX] += value;
        length += deltaLen;
        width += deltaWid;

        return false;
    }

    uint64_t get(const uint16_t &i, const uint16_t &j) {

        return a[i][j];
    }

    void printArray() {
        for (uint16_t i = 0; i < length; ++i) {
            for (uint16_t j = 0; j < width; ++j) {
                printf("%5llu", a[i][j]);
            }
            std::cout << '\n';
        }
        std::cout << "\n";
    }

    void deleteArray(uint64_t** tmp, const uint16_t& len) {
        for (uint16_t i = 0; i < len; ++i) {
            free(tmp[i]);
        }
        free(tmp);
    }

    uint64_t** getArray() {

        return a;
    }
};

#endif //BIN_ARRAY_H
