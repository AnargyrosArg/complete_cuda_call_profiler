#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftSetWorkArea(cufftHandle plan, void *workArea)
{
	cufftResult retval = cufftSetWorkArea(plan, workArea);
	return retval;
}