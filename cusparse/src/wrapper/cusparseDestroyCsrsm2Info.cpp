#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyCsrsm2Info(csrsm2Info_t info)
{
	cusparseStatus_t retval = cusparseDestroyCsrsm2Info(info);
	return retval;
}