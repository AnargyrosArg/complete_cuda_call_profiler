#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateLRNDescriptor(cudnnLRNDescriptor_t *normDesc)
{
	cudnnStatus_t retval = cudnnCreateLRNDescriptor(normDesc);
	return retval;
}