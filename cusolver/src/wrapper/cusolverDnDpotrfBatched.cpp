#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDpotrfBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *Aarray[], int lda, int *infoArray, int batchSize)
{
	cusolverStatus_t retval = cusolverDnDpotrfBatched(handle, uplo, n, Aarray, lda, infoArray, batchSize);
	return retval;
}