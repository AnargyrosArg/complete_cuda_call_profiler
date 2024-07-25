#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroyCsric02Info(csric02Info_t info)
{
	cusparseStatus_t retval = cusparseDestroyCsric02Info(info);
	return retval;
}