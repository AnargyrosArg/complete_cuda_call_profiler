#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseLoggerForceDisable()
{
	cusparseStatus_t retval = cusparseLoggerForceDisable();
	return retval;
}