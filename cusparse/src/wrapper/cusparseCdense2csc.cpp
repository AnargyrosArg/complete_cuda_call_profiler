#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCdense2csc(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *A, int lda, const int *nnzPerCol, cuComplex *cscSortedValA, int *cscSortedRowIndA, int *cscSortedColPtrA)
{
	cusparseStatus_t retval = cusparseCdense2csc(handle, m, n, descrA, A, lda, nnzPerCol, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA);
	return retval;
}