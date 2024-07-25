#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcoo2csr(cusparseHandle_t handle, const int *cooRowInd, int nnz, int m, int *csrSortedRowPtr, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseXcoo2csr(handle, cooRowInd, nnz, m, csrSortedRowPtr, idxBase);
	return retval;
}