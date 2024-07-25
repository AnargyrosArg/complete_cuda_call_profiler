#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcscsort_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, const int *cscColPtrA, const int *cscRowIndA, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseXcscsort_bufferSizeExt(handle, m, n, nnz, cscColPtrA, cscRowIndA, pBufferSizeInBytes);
	return retval;
}