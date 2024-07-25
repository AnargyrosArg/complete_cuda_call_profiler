#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyActivationDescriptor(cudnnActivationDescriptor_t activationDesc)
{
	cudnnStatus_t retval = cudnnDestroyActivationDescriptor(activationDesc);
	return retval;
}