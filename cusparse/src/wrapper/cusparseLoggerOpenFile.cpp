#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseLoggerOpenFile(const char *logFile)
{
	cusparseStatus_t retval = cusparseLoggerOpenFile(logFile);
	return retval;
}