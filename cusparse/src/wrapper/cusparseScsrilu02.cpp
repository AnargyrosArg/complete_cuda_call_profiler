#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseScsrilu02(cusparseHandle_t handle, int m, int nnz, const cusparseMatDescr_t descrA, float *csrSortedValA_valM, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrilu02Info_t info, cusparseSolvePolicy_t policy, void *pBuffer)
{
	cusparseStatus_t retval = cusparseScsrilu02(handle, m, nnz, descrA, csrSortedValA_valM, csrSortedRowPtrA, csrSortedColIndA, info, policy, pBuffer);
	return retval;
}