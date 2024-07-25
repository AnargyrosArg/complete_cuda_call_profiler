#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftSetStream(cufftHandle plan, cudaStream_t stream)
{
	cufftResult retval = cufftSetStream(plan, stream);
	return retval;
}