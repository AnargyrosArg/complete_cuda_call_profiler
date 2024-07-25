#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuDoubleComplex *ds, cuDoubleComplex *dl, cuDoubleComplex *d, cuDoubleComplex *du, cuDoubleComplex *dw, cuDoubleComplex *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseZgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
	return retval;
}