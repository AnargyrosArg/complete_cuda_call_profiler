#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyTensorTransformDescriptor(cudnnTensorTransformDescriptor_t transformDesc)
{
	cudnnStatus_t retval = cudnnDestroyTensorTransformDescriptor(transformDesc);
	return retval;
}