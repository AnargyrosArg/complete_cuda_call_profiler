#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgtsv2StridedBatch(cusparseHandle_t handle, int m, const cuComplex *dl, const cuComplex *d, const cuComplex *du, cuComplex *x, int batchCount, int batchStride, void *pBuffer)
{
	cusparseStatus_t retval = cusparseCgtsv2StridedBatch(handle, m, dl, d, du, x, batchCount, batchStride, pBuffer);
	return retval;
}