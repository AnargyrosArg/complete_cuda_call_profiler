#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXbsrilu02_zeroPivot(cusparseHandle_t handle, bsrilu02Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXbsrilu02_zeroPivot(handle, info, position);
	return retval;
}