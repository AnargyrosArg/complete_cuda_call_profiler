#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *count)
{
	cudnnStatus_t retval = cudnnGetRNNForwardInferenceAlgorithmMaxCount(handle, rnnDesc, count);
	return retval;
}