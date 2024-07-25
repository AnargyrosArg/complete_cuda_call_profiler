#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcoosort_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, const int *cooRowsA, const int *cooColsA, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseXcoosort_bufferSizeExt(handle, m, n, nnz, cooRowsA, cooColsA, pBufferSizeInBytes);
	return retval;
}