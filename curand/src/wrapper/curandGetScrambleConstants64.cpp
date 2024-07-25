#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGetScrambleConstants64(unsigned long long **constants)
{
	curandStatus_t retval = curandGetScrambleConstants64(constants);
	return retval;
}