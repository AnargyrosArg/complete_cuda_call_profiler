#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgtsv2StridedBatch(cusparseHandle_t handle, int m, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, cuDoubleComplex *x, int batchCount, int batchStride, void *pBuffer)
{
	cusparseStatus_t retval = cusparseZgtsv2StridedBatch(handle, m, dl, d, du, x, batchCount, batchStride, pBuffer);
	return retval;
}