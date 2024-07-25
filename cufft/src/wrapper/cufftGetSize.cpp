#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetSize(cufftHandle handle, size_t *workSize)
{
	cufftResult retval = cufftGetSize(handle, workSize);
	return retval;
}