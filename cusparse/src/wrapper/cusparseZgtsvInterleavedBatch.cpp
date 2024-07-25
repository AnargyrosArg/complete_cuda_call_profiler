#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuDoubleComplex *dl, cuDoubleComplex *d, cuDoubleComplex *du, cuDoubleComplex *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseZgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
	return retval;
}