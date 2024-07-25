#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXbsrsm2_zeroPivot(cusparseHandle_t handle, bsrsm2Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXbsrsm2_zeroPivot(handle, info, position);
	return retval;
}