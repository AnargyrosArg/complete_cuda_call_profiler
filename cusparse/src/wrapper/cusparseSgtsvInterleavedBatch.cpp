#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, float *dl, float *d, float *du, float *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseSgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
	return retval;
}