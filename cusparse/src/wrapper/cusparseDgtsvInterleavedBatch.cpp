#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, double *dl, double *d, double *du, double *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
	return retval;
}