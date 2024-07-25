#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, double *ds, double *dl, double *d, double *du, double *dw, double *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
	return retval;
}