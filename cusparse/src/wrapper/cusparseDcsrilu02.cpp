#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDcsrilu02(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, double *csrSortedValA_valM, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrilu02Info_t info, cusparseSolvePolicy_t policy, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDcsrilu02(handle, m, nnz, descrA, csrSortedValA_valM, csrSortedRowPtrA, csrSortedColIndA, info, policy, pBuffer);
	return retval;
}