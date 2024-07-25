#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetSize1d(cufftHandle handle, int nx, cufftType type, int batch, size_t *workSize)
{
	cufftResult retval = cufftGetSize1d(handle, nx, type, batch, workSize);
	return retval;
}