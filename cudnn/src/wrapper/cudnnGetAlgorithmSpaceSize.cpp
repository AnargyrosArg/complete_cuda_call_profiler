#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetAlgorithmSpaceSize(cudnnHandle_t handle, cudnnAlgorithmDescriptor_t algoDesc, size_t *algoSpaceSizeInBytes)
{
	cudnnStatus_t retval = cudnnGetAlgorithmSpaceSize(handle, algoDesc, algoSpaceSizeInBytes);
	return retval;
}