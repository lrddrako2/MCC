# include <iostream>
# include <lapacke.h>

int main() {
    //Matriz A (2x2)
    double A[4] = {3, 1, 2, 4}; //Nota: dice que está ordenado en formato columna mayor
    // el Vector b:
    double b[2] = {5, 6};
    //Dimensiones:
    int n = 2; // Es el nro de rows/columns de A (Matriz cuadrada)
    int nrhs = 1; // nro de columns en b( xq es un vector)
    int lda = 2; // Leading dimensions de A
    int ldb = 2; // Leading dimension de b
    // Variables de pivoteo y estado
    int ipiv[2]; // Es un array para las permutaciones pivot
    int info; // Codigo de retorno de LAPACK
    
    // LLamar a LAPACK para resolver el sistema:
    info = LAPACKE_dgesv(LAPACK_COL_MAJOR, n, nrhs, A, lda, ipiv, b, ldb);
    if (info == 0) {
        std::cout << "El sistema se resolvió con éxito.\n";
        std::cout << "Solución:\n";
        for(int i = 0; i < n; ++i) {
            std::cout << "x [" << i << "] = "<< b[i] << "\n";
        }
    }   else {
        std::cerr << "Error al resolver el sistema, código: " << info << "\n";
    }
    return 0;
}
