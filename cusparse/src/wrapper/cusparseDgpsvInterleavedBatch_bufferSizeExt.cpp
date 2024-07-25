#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const double *ds, const double *dl, const double *d, const double *du, const double *dw, const double *x, int batchCount, size_t *pBufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseDgpsvInterleavedBatch_bufferSizeExt(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBufferSizeInBytes);
	return retval;
}