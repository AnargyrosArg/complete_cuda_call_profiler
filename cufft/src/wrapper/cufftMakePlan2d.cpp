#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftMakePlan2d(cufftHandle plan, int nx, int ny, cufftType type, size_t *workSize)
{
	cufftResult retval = cufftMakePlan2d(plan, nx, ny, type, workSize);
	return retval;
}