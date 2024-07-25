#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateFilterDescriptor(cudnnFilterDescriptor_t *filterDesc)
{
	cudnnStatus_t retval = cudnnCreateFilterDescriptor(filterDesc);
	return retval;
}