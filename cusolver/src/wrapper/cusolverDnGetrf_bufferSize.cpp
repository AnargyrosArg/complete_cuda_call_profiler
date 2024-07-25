#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnGetrf_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, int64_t m, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType computeType, size_t *workspaceInBytes)
{
	cusolverStatus_t retval = cusolverDnGetrf_bufferSize(handle, params, m, n, dataTypeA, A, lda, computeType, workspaceInBytes);
	return retval;
}