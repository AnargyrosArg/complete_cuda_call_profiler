#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateDropoutDescriptor(cudnnDropoutDescriptor_t *dropoutDesc)
{
	cudnnStatus_t retval = cudnnCreateDropoutDescriptor(dropoutDesc);
	return retval;
}