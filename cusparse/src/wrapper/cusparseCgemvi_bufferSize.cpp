#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgemvi_bufferSize(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, int nnz, int *pBufferSize)
{
	cusparseStatus_t retval = cusparseCgemvi_bufferSize(handle, transA, m, n, nnz, pBufferSize);
	return retval;
}