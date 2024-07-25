#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyCsru2csrInfo(csru2csrInfo_t info)
{
	cusparseStatus_t retval = cusparseDestroyCsru2csrInfo(info);
	return retval;
}