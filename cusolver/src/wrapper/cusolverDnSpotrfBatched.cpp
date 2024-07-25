#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSpotrfBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *Aarray[], int lda, int *infoArray, int batchSize)
{
	cusolverStatus_t retval = cusolverDnSpotrfBatched(handle, uplo, n, Aarray, lda, infoArray, batchSize);
	return retval;
}