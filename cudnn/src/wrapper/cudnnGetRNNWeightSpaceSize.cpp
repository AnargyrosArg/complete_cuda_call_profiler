#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetRNNWeightSpaceSize(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, size_t *weightSpaceSize)
{
	cudnnStatus_t retval = cudnnGetRNNWeightSpaceSize(handle, rnnDesc, weightSpaceSize);
	return retval;
}