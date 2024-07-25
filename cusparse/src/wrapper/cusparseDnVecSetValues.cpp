#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnVecSetValues(cusparseDnVecDescr_t dnVecDescr, void *values)
{
	cusparseStatus_t retval = cusparseDnVecSetValues(dnVecDescr, values);
	return retval;
}