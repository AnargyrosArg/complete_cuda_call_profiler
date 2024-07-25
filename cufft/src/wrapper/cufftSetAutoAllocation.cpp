#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftSetAutoAllocation(cufftHandle plan, int autoAllocate)
{
	cufftResult retval = cufftSetAutoAllocation(plan, autoAllocate);
	return retval;
}