#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyPruneInfo(pruneInfo_t info)
{
	cusparseStatus_t retval = cusparseDestroyPruneInfo(info);
	return retval;
}