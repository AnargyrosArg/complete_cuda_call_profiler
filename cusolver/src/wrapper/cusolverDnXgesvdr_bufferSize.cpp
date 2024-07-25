#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXgesvdr_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, signed char jobu, signed char jobv, int64_t m, int64_t n, int64_t k, int64_t p, int64_t niters, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType dataTypeSrand, const void *Srand, cudaDataType dataTypeUrand, const void *Urand, int64_t ldUrand, cudaDataType dataTypeVrand, const void *Vrand, int64_t ldVrand, cudaDataType computeType, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost)
{
	cusolverStatus_t retval = cusolverDnXgesvdr_bufferSize(handle, params, jobu, jobv, m, n, k, p, niters, dataTypeA, A, lda, dataTypeSrand, Srand, dataTypeUrand, Urand, ldUrand, dataTypeVrand, Vrand, ldVrand, computeType, workspaceInBytesOnDevice, workspaceInBytesOnHost);
	return retval;
}