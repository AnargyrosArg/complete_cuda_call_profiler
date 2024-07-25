#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSbsrilu02_numericBoost(cusparseHandle_t handle, bsrilu02Info_t info, int enable_boost, double *tol, float *boost_val)
{
	cusparseStatus_t retval = cusparseSbsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
	return retval;
}