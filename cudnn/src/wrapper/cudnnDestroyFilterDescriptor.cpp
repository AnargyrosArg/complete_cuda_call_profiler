#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyFilterDescriptor(cudnnFilterDescriptor_t filterDesc)
{
	cudnnStatus_t retval = cudnnDestroyFilterDescriptor(filterDesc);
	return retval;
}