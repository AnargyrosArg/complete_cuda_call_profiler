#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZdense2csr(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *A, int lda, const int *nnzPerRow, cuDoubleComplex *csrSortedValA, int *csrSortedRowPtrA, int *csrSortedColIndA)
{
	cusparseStatus_t retval = cusparseZdense2csr(handle, m, n, descrA, A, lda, nnzPerRow, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA);
	return retval;
}