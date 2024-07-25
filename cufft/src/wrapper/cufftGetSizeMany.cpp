#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cufftResult wrapper_cufftGetSizeMany(cufftHandle handle, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, cufftType type, int batch, size_t *workArea)
{
	cufftResult retval = cufftGetSizeMany(handle, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workArea);
	return retval;
}