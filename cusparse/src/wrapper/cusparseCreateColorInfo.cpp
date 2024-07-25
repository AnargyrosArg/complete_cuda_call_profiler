#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateColorInfo(cusparseColorInfo_t *info)
{
	cusparseStatus_t retval = cusparseCreateColorInfo(info);
	return retval;
}