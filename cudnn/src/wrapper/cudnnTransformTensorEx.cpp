#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnTransformTensorEx(cudnnHandle_t handle, const cudnnTensorTransformDescriptor_t transDesc, const void *alpha, const cudnnTensorDescriptor_t srcDesc, const void *srcData, const void *beta, const cudnnTensorDescriptor_t destDesc, void *destData)
{
	cudnnStatus_t retval = cudnnTransformTensorEx(handle, transDesc, alpha, srcDesc, srcData, beta, destDesc, destData);
	return retval;
}