#include "matrix.h"
#include <unistd.h>

struct executorParams {
    int calculated;
    const matrix &left;
    const matrix &right;
    matrix &result;
};

struct writerParams {
    std::ofstream &out;
    const matrix &result;
};

pthread_mutex_t calculated_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t matrix_mutex = PTHREAD_MUTEX_INITIALIZER;


void *calculateElem(void *args) {
    auto *params = (executorParams *) (args);
    int idx;
    while (true) {
        pthread_mutex_lock(&calculated_mutex);
        idx = params->calculated;
        params->calculated++;
        pthread_mutex_unlock(&calculated_mutex);
        if (idx < params->result.getX() * params->result.getY()) {
            int horizontal = idx / params->result.getY();
            int vertical = idx % params->result.getY();
            std::vector<double> row = params->left.getRow(horizontal);
            std::vector<double> verticalLine = params->right.getLine(vertical);
            double res = 0;
            for (int i = 0; i < row.size(); i++) {
                res += row[i] * verticalLine[i];
            }
            pthread_mutex_lock(&matrix_mutex);
            params->result.setCell(horizontal, vertical, res);
            pthread_mutex_unlock(&matrix_mutex);
            usleep(1000);
        } else {
            break;
        }
    }
    return nullptr;
}

void *writeMatrix(void *args) {
    auto *params = (writerParams *) args;
    params->result.print(params->out);
    return nullptr;
}

matrix matrix::multiply(const matrix &left, const matrix &right, int p, std::ofstream &out) {

    matrix new_matrix(left.x, right.y);
    std::vector<pthread_t> executors(p);
    executorParams executorParams{0, left, right, new_matrix};

    for (int i = 0; i < p; i++) {
        if (pthread_create(&executors[i], nullptr, calculateElem, &executorParams) !=
            0) {
            std::cerr << "Cannot create threads" << std::endl;
            exit(-1);
        }
    }

    for (int i = 0; i < p; i++) {
        pthread_join(executors[i], nullptr);
    }

    writerParams writeInfo{out, new_matrix};
    pthread_t writer;
    if (pthread_create(&writer, nullptr, writeMatrix, &writeInfo) != 0) {
        std::cerr << "Cannot create threads" << std::endl;
        exit(-1);
    }
    pthread_join(writer, nullptr);
    return new_matrix;

}