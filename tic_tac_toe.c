#include <stdbool.h>

bool game_check(char tabla[3][3], char jucator_curent) {
    for (int i = 0; i < 3; i++) {
        if (tabla[i][0] == jucator_curent &&
            tabla[i][1] == jucator_curent &&
            tabla[i][2] == jucator_curent)
            return true;
    }

    for (int j = 0; j < 3; j++) {
        if (tabla[0][j] == jucator_curent &&
            tabla[1][j] == jucator_curent &&
            tabla[2][j] == jucator_curent)
            return true;
    }

    if (tabla[0][0] == jucator_curent &&
        tabla[1][1] == jucator_curent &&
        tabla[2][2] == jucator_curent)
        return true;

    if (tabla[0][2] == jucator_curent &&
        tabla[1][1] == jucator_curent &&
        tabla[2][0] == jucator_curent)
        return true;

    return false;
}