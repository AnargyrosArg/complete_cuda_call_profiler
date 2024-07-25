#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSyevdx_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, void *vl, void *vu, int64_t il, int64_t iu, int64_t *h_meig, cudaDataType dataTypeW, const void *W, cudaDataType computeType, size_t *workspaceInBytes)
{
	cusolverStatus_t retval = cusolverDnSyevdx_bufferSize(handle, params, jobz, range, uplo, n, dataTypeA, A, lda, vl, vu, il, iu, h_meig, dataTypeW, W, computeType, workspaceInBytes);
	return retval;
}