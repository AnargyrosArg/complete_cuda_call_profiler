#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZcsc2dense(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *cscSortedValA, const int *cscSortedRowIndA, const int *cscSortedColPtrA, cuDoubleComplex *A, int lda)
{
	cusparseStatus_t retval = cusparseZcsc2dense(handle, m, n, descrA, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA, A, lda);
	return retval;
}