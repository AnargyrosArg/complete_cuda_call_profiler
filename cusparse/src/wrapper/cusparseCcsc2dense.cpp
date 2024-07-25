#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCcsc2dense(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *cscSortedValA, const int *cscSortedRowIndA, const int *cscSortedColPtrA, cuComplex *A, int lda)
{
	cusparseStatus_t retval = cusparseCcsc2dense(handle, m, n, descrA, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA, A, lda);
	return retval;
}