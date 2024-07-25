#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *count)
{
	cudnnStatus_t retval = cudnnGetRNNForwardTrainingAlgorithmMaxCount(handle, rnnDesc, count);
	return retval;
}