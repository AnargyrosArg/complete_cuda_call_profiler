#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroySpVec(cusparseSpVecDescr_t spVecDescr)
{
	cusparseStatus_t retval = cusparseDestroySpVec(spVecDescr);
	return retval;
}