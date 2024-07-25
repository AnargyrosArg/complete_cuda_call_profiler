#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpSM_destroyDescr(cusparseSpSMDescr_t descr)
{
	cusparseStatus_t retval = cusparseSpSM_destroyDescr(descr);
	return retval;
}