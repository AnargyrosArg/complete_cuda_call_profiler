#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnActivationForward(cudnnHandle_t handle, cudnnActivationDescriptor_t activationDesc, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *beta, const cudnnTensorDescriptor_t yDesc, void *y)
{
	cudnnStatus_t retval = cudnnActivationForward(handle, activationDesc, alpha, xDesc, x, beta, yDesc, y);
	return retval;
}