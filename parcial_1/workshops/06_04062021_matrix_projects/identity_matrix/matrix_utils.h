#pragma once
#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <chrono>
#include <vector>
#include <regex>

class MatrixUtils {
public:
    /**
     * @brief llena una matriz de valores aleatorios generados entre un minimo y maximo
     *
     * @tparam T tipo de dato de la matriz
     * @param matrix matriz a ser llenada
     * @param min valor minimo a ser generado
     * @param max valor maximo a ser generado
     */
    template <typename T>
    static void fill_random(Matrix<T> &matrix, int min, int max);

    /**
     * @brief llena una matriz con un valor dado
     *
     * @tparam T tipo de dato de la matriz
     * @param matrix matriz a ser llenada
     * @param value valor con el que se llenara la matriz
     */
    template <typename T>
    static void fill(Matrix<T> &matrix, T value);

    /**
     * @brief imprime una matriz
     *
     * @tparam T tipo de dato de la matriz
     * @param matrix matriz a ser mostrada
     */
    template <typename T>
    static void print(Matrix<T> matrix);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MatrixUtils::fill_random(Matrix<T> &matrix, int min, int max) {
    std::random_device rd;
    std::uniform_int_distribution<> dist(min, max);
    static std::mt19937_64 random_generator(std::chrono::system_clock::now().time_since_epoch().count());

    int size = matrix.get_size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix.set_element(i, j, dist(random_generator));
        }
    }
}

template <typename T>
void MatrixUtils::fill(Matrix<T> &matrix, T value) {
    int size = matrix.get_size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix.set_element(i, j, value);
        }
    }
}

template <typename T>
void MatrixUtils::print(Matrix<T> matrix) {
    int m = matrix.get_size();
    int n = matrix.get_size();

    /*
    // these ASCII characters may not work with some fonts
    char tiles[] = {
        '┌', // 0: top left corner
        '┐', // 1: top right corner
        '└', // 2: bottom left corner
        '┘', // 3: bottom right corner
        '─', // 4: horizontal line
        '│', // 5: vertical line
        '┬', // 6: top separator
        '┴', // 7: bottom separator
        '├', // 8: middle left vertical line
        '┼', // 9: middle center vertical line
        '┤' // 10: middle right vertical line
    };
    */

    // fallback for the previous extended ASCII characters
    char tiles[] = {
        '+', // 0: top left corner
        '+', // 1: top right corner
        '+', // 2: bottom left corner
        '+', // 3: bottom right corner
        '-', // 4: horizontal line
        '|', // 5: vertical line
        '+', // 6: top separator
        '+', // 7: bottom separator
        '+', // 8: middle left vertical line
        '+', // 9: middle center vertical line
        '+' // 10: middle right vertical line
    };

    std::vector<int> columns_width(n);
    T **data = matrix.get_data();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int value = data[i][j];

            if (value < 0) value *= -1;
            else if (value == 0) value = 1;

            int digitLength = std::to_string(value).length();

            if (columns_width[j] < digitLength) {
                columns_width[j] = digitLength;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (i == 0) {
            // top left corner
            std::cout << tiles[0];

            for (int k = 0; k < n; k++) {
                for (int l = 0; l < (2 + columns_width[k]); l++) {
                    std::cout << tiles[4];
                }

                if (k != n - 1) {
                    std::cout << tiles[0];
                }
            }

            // top right corner
            std::cout << tiles[1];
        }

        std::cout << std::endl;

        for (int j = 0; j < n; j++) {
            int digitLength = std::to_string(data[i][j]).length();

            std::cout << tiles[5] << " ";
            std::cout << data[i][j];

            for (int l = 0; l < columns_width[j] - digitLength + 1; l++) {
                std::cout << " ";
            }

            if (j == (n - 1)) {
                std::cout << tiles[5];
            }
        }

        std::cout << std::endl;

        if (i == (m - 1)) {
            // bottom left corner
            std::cout << tiles[2];

            for (int k = 0; k < n; k++) {
                for (int l = 0; l < (2 + columns_width[k]); l++) {
                    std::cout << tiles[4];
                }

                if (k != n - 1) {
                    std::cout << tiles[7];
                }
            }

            // bottom right corner
            std::cout << tiles[3];
        } else {
            // middle left vertical line
            std::cout << tiles[8];

            for (int k = 0; k < n; k++) {
                for (int l = 0; l < (2 + columns_width[k]); l++) {
                    std::cout << tiles[4];
                }

                if (k != n - 1) {
                    std::cout << tiles[9];
                }
            }

            // middle right vertical line
            std::cout << tiles[10];
        }
    }

    std::cout << std::endl;
}
