#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyAlgorithmDescriptor(cudnnAlgorithmDescriptor_t algoDesc)
{
	cudnnStatus_t retval = cudnnDestroyAlgorithmDescriptor(algoDesc);
	return retval;
}