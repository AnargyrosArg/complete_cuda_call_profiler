#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftDestroy(cufftHandle plan)
{
	cufftResult retval = cufftDestroy(plan);
	return retval;
}