#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateActivationDescriptor(cudnnActivationDescriptor_t *activationDesc)
{
	cudnnStatus_t retval = cudnnCreateActivationDescriptor(activationDesc);
	return retval;
}