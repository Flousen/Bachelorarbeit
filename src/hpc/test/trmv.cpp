#include <complex>
#include <functional>
#include <random>

#include <printf.hpp>

#include <hpc/matvec.hpp>
#include <hpc/matvec/test/error.hpp>
#include <hpc/matvec/test/rand.hpp>
#include <hpc/matvec/test/walltime.hpp>
#include <hpc/matvec/test/diagdom.hpp>

#include <hpc/mklblas.hpp>


// from intel mkl
#include <mkl_types.h>
#include <mkl_lapack.h>
#define MAX_M 5 
#define MAX_N 5


int
main()
{
    using namespace hpc::matvec;

    GeMatrix<double> A(MAX_M, MAX_N, Order::ColMajor);
    DenseVector<double> x(A.numCols());
    
    GeMatrix<double> C(MAX_M, MAX_N, Order::ColMajor);
    DenseVector<double> y(A.numCols());

    test::rand(A);
    copy(A.row(0,0), x);

    copy(A.row(0,0), y);
    copy(A, C);

    auto B = A.view(UpLo::Upper);
    auto D = C.view(UpLo::Upper);

    fmt::printf("B = \n"); print(B, "%9.4f");
    fmt::printf("x = \n"); print(x, "%9.4f");
    
    fmt::printf("D = \n"); print(D, "%9.4f");
    fmt::printf("y = \n"); print(y, "%9.4f");
    
    hpc::matvec::mv(1.0, B, x);    
    hpc::mklblas::mv(1.0, D, y);    
    
    fmt::printf("matvec A*x = \n"); print(x, "%9.4f");
    fmt::printf("mkl A*x = \n"); print(y, "%9.4f");

}
