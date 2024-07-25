#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCpotrfBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *Aarray[], int lda, int *infoArray, int batchSize)
{
	cusolverStatus_t retval = cusolverDnCpotrfBatched(handle, uplo, n, Aarray, lda, infoArray, batchSize);
	return retval;
}