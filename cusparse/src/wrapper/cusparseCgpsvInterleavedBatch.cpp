#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, cuComplex *ds, cuComplex *dl, cuComplex *d, cuComplex *du, cuComplex *dw, cuComplex *x, int batchCount, void *pBuffer)
{
	cusparseStatus_t retval = cusparseCgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
	return retval;
}