#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcsrsm2_zeroPivot(cusparseHandle_t handle, csrsm2Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXcsrsm2_zeroPivot(handle, info, position);
	return retval;
}