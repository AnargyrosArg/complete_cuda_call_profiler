#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGetVersion(int *version)
{
	curandStatus_t retval = curandGetVersion(version);
	return retval;
}