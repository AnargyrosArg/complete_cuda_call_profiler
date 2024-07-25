#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuComplex *dl, cuComplex *d, cuComplex *du, cuComplex *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseCgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
	return retval;
}