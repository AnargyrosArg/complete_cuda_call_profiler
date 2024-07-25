#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetMatrixAsync(int rows, int cols, int elemSize, const void *A, int lda, void *B, int ldb, cudaStream_t stream)
{
	cublasStatus_t retval = cublasGetMatrixAsync(rows, cols, elemSize, A, lda, B, ldb, stream);
	return retval;
}