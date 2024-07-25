#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCdense2csr(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *A, int lda, const int *nnzPerRow, cuComplex *csrSortedValA, int *csrSortedRowPtrA, int *csrSortedColIndA)
{
	cusparseStatus_t retval = cusparseCdense2csr(handle, m, n, descrA, A, lda, nnzPerRow, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA);
	return retval;
}