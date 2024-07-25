#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcsrilu02_zeroPivot(cusparseHandle_t handle, csrilu02Info_t info, int *position)
{
	cusparseStatus_t retval = cusparseXcsrilu02_zeroPivot(handle, info, position);
	return retval;
}