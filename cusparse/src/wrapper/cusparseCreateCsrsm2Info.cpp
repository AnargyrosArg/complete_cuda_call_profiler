#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateCsrsm2Info(csrsm2Info_t *info)
{
	cusparseStatus_t retval = cusparseCreateCsrsm2Info(info);
	return retval;
}