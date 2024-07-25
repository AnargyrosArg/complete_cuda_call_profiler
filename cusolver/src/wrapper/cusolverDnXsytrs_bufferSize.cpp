#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXsytrs_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int64_t n, int64_t nrhs, cudaDataType dataTypeA, const void *A, int64_t lda, const int64_t *ipiv, cudaDataType dataTypeB, void *B, int64_t ldb, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost)
{
	cusolverStatus_t retval = cusolverDnXsytrs_bufferSize(handle, uplo, n, nrhs, dataTypeA, A, lda, ipiv, dataTypeB, B, ldb, workspaceInBytesOnDevice, workspaceInBytesOnHost);
	return retval;
}