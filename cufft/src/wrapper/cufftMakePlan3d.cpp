#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftMakePlan3d(cufftHandle plan, int nx, int ny, int nz, cufftType type, size_t *workSize)
{
	cufftResult retval = cufftMakePlan3d(plan, nx, ny, nz, type, workSize);
	return retval;
}