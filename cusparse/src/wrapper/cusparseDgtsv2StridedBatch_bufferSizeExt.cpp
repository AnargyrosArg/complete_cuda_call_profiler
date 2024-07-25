#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t handle, int m, const double *dl, const double *d, const double *du, const double *x, int batchCount, int batchStride, size_t *bufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseDgtsv2StridedBatch_bufferSizeExt(handle, m, dl, d, du, x, batchCount, batchStride, bufferSizeInBytes);
	return retval;
}