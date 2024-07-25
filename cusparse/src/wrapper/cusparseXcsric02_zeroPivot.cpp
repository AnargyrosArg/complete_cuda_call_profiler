#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcsric02_zeroPivot(cusparseHandle_t handle, csric02Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXcsric02_zeroPivot(handle, info, position);
	return retval;
}