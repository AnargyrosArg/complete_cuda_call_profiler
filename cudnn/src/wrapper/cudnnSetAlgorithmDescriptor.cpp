#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetAlgorithmDescriptor(cudnnAlgorithmDescriptor_t algoDesc, cudnnAlgorithm_t algorithm)
{
	cudnnStatus_t retval = cudnnSetAlgorithmDescriptor(algoDesc, algorithm);
	return retval;
}