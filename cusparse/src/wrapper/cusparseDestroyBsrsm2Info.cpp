#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyBsrsm2Info(bsrsm2Info_t info)
{
	cusparseStatus_t retval = cusparseDestroyBsrsm2Info(info);
	return retval;
}