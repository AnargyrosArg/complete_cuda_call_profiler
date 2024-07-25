#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseGetProperty(libraryPropertyType type, int *value)
{
	cusparseStatus_t retval = cusparseGetProperty(type, value);
	return retval;
}