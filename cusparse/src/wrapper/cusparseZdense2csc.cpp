#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZdense2csc(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *A, int lda, const int *nnzPerCol, cuDoubleComplex *cscSortedValA, int *cscSortedRowIndA, int *cscSortedColPtrA)
{
	cusparseStatus_t retval = cusparseZdense2csc(handle, m, n, descrA, A, lda, nnzPerCol, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA);
	return retval;
}