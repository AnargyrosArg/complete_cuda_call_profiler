#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cusparseGetErrorString(cusparseStatus_t status)
{
	const char * retval = cusparseGetErrorString(status);
	return retval;
}