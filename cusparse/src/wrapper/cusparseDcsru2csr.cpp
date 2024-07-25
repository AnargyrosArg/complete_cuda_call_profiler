#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDcsru2csr(cusparseHandle_t handle, int m, int n, int nnz, const cusparseMatDescr_t descrA, double *csrVal, const int *csrRowPtr, int *csrColInd, csru2csrInfo_t info, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDcsru2csr(handle, m, n, nnz, descrA, csrVal, csrRowPtr, csrColInd, info, pBuffer);
	return retval;
}