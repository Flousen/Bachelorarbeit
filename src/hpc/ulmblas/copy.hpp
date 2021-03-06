#ifndef HPC_ULMBLAS_COPY_HPP
#define HPC_ULMBLAS_COPY_HPP

#include <cstddef>
#include <hpc/tools/conjugate.hpp>

namespace hpc { namespace ulmblas {

/// - copy function for vectors (that can have different element types)
template <typename TX, typename TY>
void
copy(std::size_t n,
     bool conjX, const TX *x, std::ptrdiff_t incX,
     TY *y, std::ptrdiff_t incY)
{
    for (std::size_t i=0; i<n; ++i) {
        y[i*incY] = tools::conjugate(x[i*incX], conjX);
    }
}

/// - copy function for matrices (that can have different element types)
template <typename TA, typename TB>
void
gecopy(std::size_t m, size_t n,
       bool conjA, const TA *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA,
       TB *B, std::ptrdiff_t incRowB, std::ptrdiff_t incColB)
{
    if (m==0 || n==0) {
        return;
    }
    // if B is row major:   B^T <- A^T
    if (incRowB>incColB) {
        gecopy(n, m, conjA, A, incColA, incRowA, B, incColB, incRowB);
        return;
    }
    // B is col major:
    for (std::size_t j=0; j<n; ++j) {
        for (std::size_t i=0; i<m; ++i) {
            B[i*incRowB+j*incColB]
                = tools::conjugate(A[i*incRowA+j*incColA], conjA);
        }

    }
}
///-

} } // namespace ulmblas, hpc

#endif // HPC_ULMBLAS_COPY_HPP
