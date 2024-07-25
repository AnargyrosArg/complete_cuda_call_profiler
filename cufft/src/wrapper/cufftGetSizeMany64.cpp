#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetSizeMany64(cufftHandle plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, long long int *onembed, long long int ostride, long long int odist, cufftType type, long long int batch, size_t *workSize)
{
	cufftResult retval = cufftGetSizeMany64(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
	return retval;
}