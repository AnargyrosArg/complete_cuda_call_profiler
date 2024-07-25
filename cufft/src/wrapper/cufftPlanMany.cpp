#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftPlanMany(cufftHandle *plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, cufftType type, int batch)
{
	cufftResult retval = cufftPlanMany(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch);
	return retval;
}