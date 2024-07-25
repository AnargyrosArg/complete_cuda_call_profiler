#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCcsru2csr_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, cuComplex *csrVal, const int *csrRowPtr, int *csrColInd, csru2csrInfo_t info, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseCcsru2csr_bufferSizeExt(handle, m, n, nnz, csrVal, csrRowPtr, csrColInd, info, pBufferSizeInBytes);
	return retval;
}