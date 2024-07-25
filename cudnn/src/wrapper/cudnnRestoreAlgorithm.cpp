#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnRestoreAlgorithm(cudnnHandle_t handle, void *algoSpace, size_t algoSpaceSizeInBytes, cudnnAlgorithmDescriptor_t algoDesc)
{
	cudnnStatus_t retval = cudnnRestoreAlgorithm(handle, algoSpace, algoSpaceSizeInBytes, algoDesc);
	return retval;
}