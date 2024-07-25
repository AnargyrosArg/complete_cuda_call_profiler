#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDivisiveNormalizationForward(cudnnHandle_t handle, cudnnLRNDescriptor_t normDesc, cudnnDivNormMode_t mode, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *means, void *temp, void *temp2, const void *beta, const cudnnTensorDescriptor_t yDesc, void *y)
{
	cudnnStatus_t retval = cudnnDivisiveNormalizationForward(handle, normDesc, mode, alpha, xDesc, x, means, temp, temp2, beta, yDesc, y);
	return retval;
}