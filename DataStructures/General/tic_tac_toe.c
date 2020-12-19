
#include <stdlib.h>

enum pos_ {
    POS_E, // empty
    POS_0, // a circle
    POS_X, // a cross
};

typedef enum pos_ pos;

typedef enum result_ {
    WON_0,
    WON_X,
    NOT_WON,
} result;

int matrix[3][3];

result check_line (int mat[][3], int e0i, int e0j, 
                  int e1i, int e1j, 
                  int e2i, int e2j) {

    if (mat[e0i][e0j] == mat[e1i][e1j] == mat[e2i][e2j]) {
        if (mat[e0i][e0j] == POS_0) {
            return WON_0;
        } else if (mat[e0i][e0j] == POS_X) {
            return WON_X;
        }
    }
    return NOT_WON;
}

result check_ttt (int mat[][3]) {
    int i, result;
    for (i=0; i<3; i++) {
        result = check_line(mat, i,0, i,1, i,2);
        if ((result == WON_X) || (result == WON_0)) {
            return result;
        }
        result = check_line(mat, 0,i, 1,i, 2,i);
        if ((result == WON_X) || (result == WON_0)) {
            return result;
        }
    }

    result = check_line(mat, 0,0, 1,1, 2,2);
    if ((result == WON_X) || (result == WON_0)) {
        return result;
    }
    return check_line(mat, 0,2, 1,1, 2,0);
}

void drawBoard (int board[][3]) {
    int i,j;
    for(i=0;i<3;i++) {
        printf("\n");
        for (j=0;j<3;j++) {
            char c = '-';
            if (board[i][j] == POS_0) c = '0';
            if (board[i][j] == POS_X) c = 'X';
            printf("%c\t", c);
        }
    }
    printf("\n\n");
}

void start (int mat[] [3]) {
    while (1) {
        
    }
}

int main (void) {
    drawBoard(matrix);
    start();
}
