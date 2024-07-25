#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGetScrambleConstants32(unsigned int **constants)
{
	curandStatus_t retval = curandGetScrambleConstants32(constants);
	return retval;
}