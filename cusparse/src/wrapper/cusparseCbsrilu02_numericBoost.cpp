#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCbsrilu02_numericBoost(cusparseHandle_t handle, bsrilu02Info_t info, int enable_boost, double *tol, cuComplex *boost_val)
{
	cusparseStatus_t retval = cusparseCbsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
	return retval;
}