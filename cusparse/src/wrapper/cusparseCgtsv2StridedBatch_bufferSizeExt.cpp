#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t handle, int m, const cuComplex *dl, const cuComplex *d, const cuComplex *du, const cuComplex *x, int batchCount, int batchStride, size_t *bufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseCgtsv2StridedBatch_bufferSizeExt(handle, m, dl, d, du, x, batchCount, batchStride, bufferSizeInBytes);
	return retval;
}