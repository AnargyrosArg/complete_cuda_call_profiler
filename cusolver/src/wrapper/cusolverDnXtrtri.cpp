#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXtrtri(cusolverDnHandle_t handle, cublasFillMode_t uplo, cublasDiagType_t diag, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, void *bufferOnDevice, size_t workspaceInBytesOnDevice, void *bufferOnHost, size_t workspaceInBytesOnHost, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnXtrtri(handle, uplo, diag, n, dataTypeA, A, lda, bufferOnDevice, workspaceInBytesOnDevice, bufferOnHost, workspaceInBytesOnHost, devInfo);
	return retval;
}