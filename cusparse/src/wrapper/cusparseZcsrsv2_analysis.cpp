#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZcsrsv2_analysis(cusparseHandle_t handle, cusparseOperation_t transA, int m, int nnz, const cusparseMatDescr_t descrA, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrsv2Info_t info, cusparseSolvePolicy_t policy, void *pBuffer)
{
	cusparseStatus_t retval = cusparseZcsrsv2_analysis(handle, transA, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, policy, pBuffer);
	return retval;
}