#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetVersion(int *version)
{
	cufftResult retval = cufftGetVersion(version);
	return retval;
}