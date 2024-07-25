#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpVecSetValues(cusparseSpVecDescr_t spVecDescr, void *values)
{
	cusparseStatus_t retval = cusparseSpVecSetValues(spVecDescr, values);
	return retval;
}