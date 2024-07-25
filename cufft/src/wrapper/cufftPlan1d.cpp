#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftPlan1d(cufftHandle *plan, int nx, cufftType type, int batch)
{
	cufftResult retval = cufftPlan1d(plan, nx, type, batch);
	return retval;
}