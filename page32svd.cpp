#include <iostream>
#include <vector> // para asignar memoria dinámica
#include <cblas.h>

// Elaborado por Jamil Gustavo Cahuana Sarmiento
// Programa para calcular la SVD de la matriz 2x2 de la página 32 del slide 3.2

extern "C" {
    void dgesvd_(char* jobu, char* jobvt,
                 int* m, int* n,
                 double* a, int* lda,
                 double* s,
                 double* u, int* ldu,
                 double* vt, int* ldvt,
                 double* work, int* lwork,
                 int* info);
}

using namespace std;

int main() {

    // Como A es 2x2 entonces declaramos:
    const int m = 2, n =2;

    // A = U*S*VT
    /* 
    Estos son los datos que nos da el enunciado,
    pero estos no podemos usarlos para hallar A ya que
    U es 3x3, S es 3x2 y VT es 2x2, por lo que la
    multiplicación no es posible.

    Por lo tanto, usaremos los datos obtenidos con:
    DGESVD, un arreglo de
    https://netlib.org/lapack/explore-html//d1/d7f/group__gesvd_gac6bd5d4e645049e49bb70691180abf07.html

    double U[]= {-0.79, -0.38, -0.48,
                0, -0.78, 0.62,
                -0.62, 0.49, 0.62};
    
    double S[]= {1.62, 0, 0,
                0, 1.0, 0,
                0, 0, 0};
    
    double VT[]= {-0.78, -0.62,
                0.62, -0.78};
    */


    double A[4] = {
        1.0, 0.0,
       -0.8, 1.0
    };

    // Copia de A (porque dgesvd la va a sobreescribir)
    double A_copy[4];
    double S[2];
    double U[4];
    double VT[4];
    double US[4];
    // m y n ya definidos arriba
    int lda = m, ldu = m, ldvt = n;
    int info;
    int lwork = -1; // Consulta por el tamaño óptimo del workspace
    double wkopt; // Tamaño óptimo del workspace

    // ---------------- SVD(LAPACK) --------------
    // Consulta por el tamaño óptimo de workspace
    // AQUÍ LA MATRIZ A ES SOBRESCRITA NO SE CALCULA LA SVD
    copy(A, A + 4, A_copy);
    dgesvd_((char*)"A", (char*)"A",
            (int*)&m, (int*)&n,
            A_copy, &lda,
            S,
            U, &ldu,
            VT, &ldvt,
            &wkopt, &lwork,
            &info);

    lwork = (int)wkopt; // Tamaño óptimo del workspace asignado
    vector<double> work(lwork);

    // Cálculo de la SVD
    dgesvd_((char*)"A", (char*)"A",
            (int*)&m, (int*)&n,
            A_copy, &lda,
            S,
            U, &ldu,
            VT, &ldvt,
            work.data(), &lwork,
            &info);
    if (info != 0) {
        cerr << "Error en SVD, info = " << info << "\n";
        return 1;
    }

    // ---------------- Reconstrucción (CBLAS) --------------
    // Hacemos esto porque dgesvd no nos da Sigma como matriz con los 2 valores únicos
    double Sigma[4] = {
        S[0], 0.0,
        0.0, S[1]
    };

    // Para multiplicar Sigma * U y obtener US
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                n, n, n,
                1.0, U, n,
                Sigma, n,
                0.0, US, n);

    double A_Reconstruido[4];
    
    // Para multiplicar US * VT y hallar A
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                n, n, n,
                1.0, US, n,
                VT, n,
                0.0, A_Reconstruido, n);

    cout << "Matriz A reconstruida: " << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << A_Reconstruido[j * 2 + i] << " ";
        }
        cout << endl;
    }
    cout << endl;
                   
    return 0;
}