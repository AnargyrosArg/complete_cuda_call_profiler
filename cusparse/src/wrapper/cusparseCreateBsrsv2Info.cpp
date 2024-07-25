#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateBsrsv2Info(bsrsv2Info_t *info)
{
	cusparseStatus_t retval = cusparseCreateBsrsv2Info(info);
	return retval;
}