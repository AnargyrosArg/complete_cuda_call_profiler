#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const cuComplex *dl, const cuComplex *d, const cuComplex *du, const cuComplex *x, int batchCount, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseCgtsvInterleavedBatch_bufferSizeExt(handle, algo, m, dl, d, du, x, batchCount, pBufferSizeInBytes);
	return retval;
}