#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateReduceTensorDescriptor(cudnnReduceTensorDescriptor_t *reduceTensorDesc)
{
	cudnnStatus_t retval = cudnnCreateReduceTensorDescriptor(reduceTensorDesc);
	return retval;
}