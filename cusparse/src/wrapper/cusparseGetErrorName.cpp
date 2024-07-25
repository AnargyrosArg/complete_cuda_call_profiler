#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cusparseGetErrorName(cusparseStatus_t status)
{
	const char * retval = cusparseGetErrorName(status);
	return retval;
}