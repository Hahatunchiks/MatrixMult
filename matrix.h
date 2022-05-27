#pragma once

#include <vector>
#include <pthread.h>
#include <fstream>
#include <iostream>

class matrix {
public:
    matrix(int x_, int y_) : x(x_), y(y_) {
        table = std::vector<std::vector<double>>(x, std::vector<double>(y));
    }

    static matrix multiply(const matrix &left, const matrix &right, int p, std::ofstream &out);


    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    std::vector<double> getRow(int idx) const {
        return table[idx];
    }

    std::vector<double> getLine(int idx) const {
        std::vector<double> line(x);
        for (int i = 0; i < x; i++) {
            line[i] = table[i][idx];
        }
        return line;
    }

    void setCell(int xCoord, int yCoord, double res) {
        table[xCoord][yCoord] = res;
    }

    template<class T>
    void print(T &output) const {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                output << table[i][j] << " ";
            }
            output << std::endl;
        }
    }

private:
    int x;
    int y;
    std::vector<std::vector<double>> table;
};
