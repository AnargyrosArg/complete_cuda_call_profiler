#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpruneDense2csrNnz(cusparseHandle_t handle, int m, int n, const float *A, int lda, const float *threshold, const cusparseMatDescr_t descrC, int *csrRowPtrC, int *nnzTotalDevHostPtr, void *pBuffer)
{
	cusparseStatus_t retval = cusparseSpruneDense2csrNnz(handle, m, n, A, lda, threshold, descrC, csrRowPtrC, nnzTotalDevHostPtr, pBuffer);
	return retval;
}