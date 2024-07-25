#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSyevdx(cusolverDnHandle_t handle, cusolverDnParams_t params, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, void *vl, void *vu, int64_t il, int64_t iu, int64_t *meig64, cudaDataType dataTypeW, void *W, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info)
{
	cusolverStatus_t retval = cusolverDnSyevdx(handle, params, jobz, range, uplo, n, dataTypeA, A, lda, vl, vu, il, iu, meig64, dataTypeW, W, computeType, pBuffer, workspaceInBytes, info);
	return retval;
}