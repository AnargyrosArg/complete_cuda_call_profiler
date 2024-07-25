#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateTensorTransformDescriptor(cudnnTensorTransformDescriptor_t *transformDesc)
{
	cudnnStatus_t retval = cudnnCreateTensorTransformDescriptor(transformDesc);
	return retval;
}