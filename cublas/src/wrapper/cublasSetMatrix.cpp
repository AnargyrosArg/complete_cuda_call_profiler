#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetMatrix(int rows, int cols, int elemSize, const void *A, int lda, void *B, int ldb)
{
	cublasStatus_t retval = cublasSetMatrix(rows, cols, elemSize, A, lda, B, ldb);
	return retval;
}