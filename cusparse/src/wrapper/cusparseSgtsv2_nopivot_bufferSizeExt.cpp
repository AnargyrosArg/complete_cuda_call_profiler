#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgtsv2_nopivot_bufferSizeExt(cusparseHandle_t handle, int m, int n, const float *dl, const float *d, const float *du, const float *B, int ldb, size_t *bufferSizeInBytes)
{
	cusparseStatus_t retval = cusparseSgtsv2_nopivot_bufferSizeExt(handle, m, n, dl, d, du, B, ldb, bufferSizeInBytes);
	return retval;
}