#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverGetProperty(libraryPropertyType type, int *value)
{
	cusolverStatus_t retval = cusolverGetProperty(type, value);
	return retval;
}