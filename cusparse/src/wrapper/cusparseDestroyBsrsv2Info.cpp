#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyBsrsv2Info(bsrsv2Info_t info)
{
	cusparseStatus_t retval = cusparseDestroyBsrsv2Info(info);
	return retval;
}