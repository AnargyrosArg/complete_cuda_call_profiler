#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetSize2d(cufftHandle handle, int nx, int ny, cufftType type, size_t *workSize)
{
	cufftResult retval = cufftGetSize2d(handle, nx, ny, type, workSize);
	return retval;
}