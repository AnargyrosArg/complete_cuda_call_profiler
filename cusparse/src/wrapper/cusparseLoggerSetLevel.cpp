#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseLoggerSetLevel(int level)
{
	cusparseStatus_t retval = cusparseLoggerSetLevel(level);
	return retval;
}