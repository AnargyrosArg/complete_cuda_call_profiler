#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnGeqrf(cusolverDnHandle_t handle, cusolverDnParams_t params, int64_t m, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, cudaDataType dataTypeTau, void *tau, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info)
{
	cusolverStatus_t retval = cusolverDnGeqrf(handle, params, m, n, dataTypeA, A, lda, dataTypeTau, tau, computeType, pBuffer, workspaceInBytes, info);
	return retval;
}