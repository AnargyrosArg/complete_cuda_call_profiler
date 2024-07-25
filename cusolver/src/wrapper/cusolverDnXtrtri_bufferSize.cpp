#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXtrtri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, cublasDiagType_t diag, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost)
{
	cusolverStatus_t retval = cusolverDnXtrtri_bufferSize(handle, uplo, diag, n, dataTypeA, A, lda, workspaceInBytesOnDevice, workspaceInBytesOnHost);
	return retval;
}