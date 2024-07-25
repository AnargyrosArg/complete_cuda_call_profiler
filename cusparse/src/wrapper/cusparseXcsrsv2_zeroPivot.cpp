#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcsrsv2_zeroPivot(cusparseHandle_t handle, csrsv2Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXcsrsv2_zeroPivot(handle, info, position);
	return retval;
}