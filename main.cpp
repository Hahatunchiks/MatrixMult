#include <iostream>
#include <fstream>
#include "matrix.h"

void enterMatrix(matrix &m) {
    std::cout << "Enter elements" << std::endl;
    double elem;
    for(int i = 0; i < m.getX(); i++) {
        for(int j = 0; j < m.getY(); j++) {
            std::cin >> elem;
            m.setCell(i, j, elem);
        }
    }
}

void process(int m, int n, int k, std::string &fileName, int p) {
    matrix left(m, n);
    std::cout << "Left matrix: ";
    enterMatrix(left);
    matrix right(n, k);
    std::cout << "Right matrix: ";
    enterMatrix(right);
    std::ofstream out(fileName);
    if(!out.is_open()) {
        throw std::invalid_argument("Error in fileName");
    }
    matrix result = matrix::multiply(left, right, p, out);
    result.print(std::cout);
}

// m, n, k, out, amount_of_threads
int main(int argc, const char **argv) {
    if (argc != 6) {
        std::cerr << "Not enough arguments:"
                     "1 - m 2 - n 3 - n "
                     "4 - outFile 5 - amount of threads\n";
        return -1;
    }
    try {
        int m{std::stoi(argv[1])};
        int n{std::stoi(argv[2])};
        int k{std::stoi(argv[3])};
        int p{std::stoi(argv[5])};
        std::string fileName = argv[4];
        process(m, n, k, fileName, p);
    } catch (std::invalid_argument &ex) {
        std::cout << "Invalid argument\n";
        return -1;
    }
    return 0;
}
