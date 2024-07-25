#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftEstimate2d(int nx, int ny, cufftType type, size_t *workSize)
{
	cufftResult retval = cufftEstimate2d(nx, ny, type, workSize);
	return retval;
}