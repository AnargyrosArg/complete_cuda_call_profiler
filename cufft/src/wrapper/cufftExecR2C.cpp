#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftExecR2C(cufftHandle plan, cufftReal *idata, cufftComplex *odata)
{
	cufftResult retval = cufftExecR2C(plan, idata, odata);
	return retval;
}