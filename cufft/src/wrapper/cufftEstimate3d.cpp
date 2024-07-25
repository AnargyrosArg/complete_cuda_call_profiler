#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftEstimate3d(int nx, int ny, int nz, cufftType type, size_t *workSize)
{
	cufftResult retval = cufftEstimate3d(nx, ny, nz, type, workSize);
	return retval;
}