#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftExecC2R(cufftHandle plan, cufftComplex *idata, cufftReal *odata)
{
	cufftResult retval = cufftExecC2R(plan, idata, odata);
	return retval;
}