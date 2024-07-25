#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroySpMat(cusparseSpMatDescr_t spMatDescr)
{
	cusparseStatus_t retval = cusparseDestroySpMat(spMatDescr);
	return retval;
}