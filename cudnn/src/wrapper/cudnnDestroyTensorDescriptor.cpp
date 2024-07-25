#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyTensorDescriptor(cudnnTensorDescriptor_t tensorDesc)
{
	cudnnStatus_t retval = cudnnDestroyTensorDescriptor(tensorDesc);
	return retval;
}