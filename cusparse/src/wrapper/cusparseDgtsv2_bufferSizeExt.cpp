#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgtsv2_bufferSizeExt(cusparseHandle_t handle, int m, int n, const double *dl, const double *d, const double *du, const double *B, int ldb, size_t *bufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseDgtsv2_bufferSizeExt(handle, m, n, dl, d, du, B, ldb, bufferSizeInBytes);
	return retval;
}