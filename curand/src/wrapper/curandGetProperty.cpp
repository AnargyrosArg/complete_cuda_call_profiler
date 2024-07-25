#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGetProperty(libraryPropertyType type, int *value)
{
	curandStatus_t retval = curandGetProperty(type, value);
	return retval;
}