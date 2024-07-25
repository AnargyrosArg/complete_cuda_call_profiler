#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatSetValues(cusparseSpMatDescr_t spMatDescr, void *values)
{
	cusparseStatus_t retval = cusparseSpMatSetValues(spMatDescr, values);
	return retval;
}