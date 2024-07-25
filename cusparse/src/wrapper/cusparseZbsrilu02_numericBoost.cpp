#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZbsrilu02_numericBoost(cusparseHandle_t handle, bsrilu02Info_t info, int enable_boost, double *tol, cuDoubleComplex *boost_val)
{
	cusparseStatus_t retval = cusparseZbsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
	return retval;
}