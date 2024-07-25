#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftEstimate1d(int nx, cufftType type, int batch, size_t *workSize)
{
	cufftResult retval = cufftEstimate1d(nx, type, batch, workSize);
	return retval;
}