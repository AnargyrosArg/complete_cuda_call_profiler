#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnMatSetValues(cusparseDnMatDescr_t dnMatDescr, void *values)
{
	cusparseStatus_t retval = cusparseDnMatSetValues(dnMatDescr, values);
	return retval;
}