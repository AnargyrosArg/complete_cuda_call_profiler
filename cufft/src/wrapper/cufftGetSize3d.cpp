#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetSize3d(cufftHandle handle, int nx, int ny, int nz, cufftType type, size_t *workSize)
{
	cufftResult retval = cufftGetSize3d(handle, nx, ny, nz, type, workSize);
	return retval;
}