#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftPlan3d(cufftHandle *plan, int nx, int ny, int nz, cufftType type)
{
	cufftResult retval = cufftPlan3d(plan, nx, ny, nz, type);
	return retval;
}