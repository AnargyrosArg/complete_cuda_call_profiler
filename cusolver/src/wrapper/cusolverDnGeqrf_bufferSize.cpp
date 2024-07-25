#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnGeqrf_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, int64_t m, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType dataTypeTau, const void *tau, cudaDataType computeType, size_t *workspaceInBytes)
{
	cusolverStatus_t retval = cusolverDnGeqrf_bufferSize(handle, params, m, n, dataTypeA, A, lda, dataTypeTau, tau, computeType, workspaceInBytes);
	return retval;
}