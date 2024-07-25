#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpSV_createDescr(cusparseSpSVDescr_t *descr)
{
	cusparseStatus_t retval = cusparseSpSV_createDescr(descr);
	return retval;
}