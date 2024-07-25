#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXbsrsv2_zeroPivot(cusparseHandle_t handle, bsrsv2Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXbsrsv2_zeroPivot(handle, info, position);
	return retval;
}