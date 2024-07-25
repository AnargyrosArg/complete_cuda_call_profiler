#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateCsrsv2Info(csrsv2Info_t *info)
{
	cusparseStatus_t retval = cusparseCreateCsrsv2Info(info);
	return retval;
}