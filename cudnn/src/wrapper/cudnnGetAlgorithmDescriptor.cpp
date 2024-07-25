#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetAlgorithmDescriptor(const cudnnAlgorithmDescriptor_t algoDesc, cudnnAlgorithm_t *algorithm)
{
	cudnnStatus_t retval = cudnnGetAlgorithmDescriptor(algoDesc, algorithm);
	return retval;
}