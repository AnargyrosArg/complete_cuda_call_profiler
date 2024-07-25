#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftMakePlan1d(cufftHandle plan, int nx, cufftType type, int batch, size_t *workSize)
{
	cufftResult retval = cufftMakePlan1d(plan, nx, type, batch, workSize);
	return retval;
}