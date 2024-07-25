#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDcsrilu02_numericBoost(cusparseHandle_t handle, csrilu02Info_t info, int enable_boost, double *tol, double *boost_val)
{
	cusparseStatus_t retval = cusparseDcsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
	return retval;
}