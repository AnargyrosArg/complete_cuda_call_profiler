#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSaveAlgorithm(cudnnHandle_t handle, cudnnAlgorithmDescriptor_t algoDesc, void *algoSpace, size_t algoSpaceSizeInBytes)
{
	cudnnStatus_t retval = cudnnSaveAlgorithm(handle, algoDesc, algoSpace, algoSpaceSizeInBytes);
	return retval;
}