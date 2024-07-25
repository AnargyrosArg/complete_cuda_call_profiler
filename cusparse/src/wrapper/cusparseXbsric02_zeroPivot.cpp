#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXbsric02_zeroPivot(cusparseHandle_t handle, bsric02Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXbsric02_zeroPivot(handle, info, position);
	return retval;
}