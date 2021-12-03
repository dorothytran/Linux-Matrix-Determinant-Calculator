/* Dorothy Tran 101141902 */
#define MATRIX_SIZE 3
#define MICRO_SEC_IN_SEC 1000000
typedef int matrix[MATRIX_SIZE][MATRIX_SIZE];

struct shared_use_st {
    matrix M;               // Matrix size initialization
    int matrix_det;         // Matrix determinant value
    int L[MATRIX_SIZE];     // Largest integer of matrix/matrix row
    int D[MATRIX_SIZE];     // Gaussian Elimination row determinant calculation
};