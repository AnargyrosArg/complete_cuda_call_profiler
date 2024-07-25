#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftCreate(cufftHandle *handle)
{
	cufftResult retval = cufftCreate(handle);
	return retval;
}