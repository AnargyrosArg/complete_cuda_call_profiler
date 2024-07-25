#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, float *ds, float *dl, float *d, float *du, float *dw, float *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseSgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
	return retval;
}