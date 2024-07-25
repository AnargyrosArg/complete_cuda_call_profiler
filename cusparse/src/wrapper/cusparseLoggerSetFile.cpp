#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseLoggerSetFile(FILE *file)
{
	cusparseStatus_t retval = cusparseLoggerSetFile(file);
	return retval;
}