#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpSV_destroyDescr(cusparseSpSVDescr_t descr)
{
	cusparseStatus_t retval = cusparseSpSV_destroyDescr(descr);
	return retval;
}