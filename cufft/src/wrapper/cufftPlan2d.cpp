#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftPlan2d(cufftHandle *plan, int nx, int ny, cufftType type)
{
	cufftResult retval = cufftPlan2d(plan, nx, ny, type);
	return retval;
}