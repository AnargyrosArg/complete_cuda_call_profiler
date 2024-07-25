#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSyevd(cusolverDnHandle_t handle, cusolverDnParams_t params, cusolverEigMode_t jobz, cublasFillMode_t uplo, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, cudaDataType dataTypeW, void *W, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info)
{
	cusolverStatus_t retval = cusolverDnSyevd(handle, params, jobz, uplo, n, dataTypeA, A, lda, dataTypeW, W, computeType, pBuffer, workspaceInBytes, info);
	return retval;
}