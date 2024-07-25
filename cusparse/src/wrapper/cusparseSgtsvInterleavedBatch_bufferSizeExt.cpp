#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const float *dl, const float *d, const float *du, const float *x, int batchCount, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseSgtsvInterleavedBatch_bufferSizeExt(handle, algo, m, dl, d, du, x, batchCount, pBufferSizeInBytes);
	return retval;
}