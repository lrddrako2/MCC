//
//  lapack.cpp
//  
//
//  Created by Jamil Cahuana on 13/12/25.
//

#include <iostream>
#include <lapacke.h>


int main() {
//    Array 1
    double A[9] = {4,2,3,3,7,1,2,1,8};
    double b[3] = {10,19,17};
//    Los siguientes datos indican:
//    n = número de columnas de A,
//    nrhs = número de columnas de b,
//    lda = indica el orden de la matriz A,
//    ldb = indica el orden de la mtriz b
    int n = 3, nrhs = 1, lda = 3, ldb = 3;
    
//    este es un array para las permutaciones pivot
    int ipiv[3], info;
    
    //    Para esolver Ax=b
// Aqui llamamos a Lapack para resolver el sistema:

    info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, A, lda, ipiv, b, ldb);
    if (info == 0) {
        std::cout << "Solution: ";
        for (int i = 0; i < n; i++) {
            std::cout << b[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Error al resolver el sistema, codigo: "
        << info << std::endl;
    }
    
    return 0;
}
