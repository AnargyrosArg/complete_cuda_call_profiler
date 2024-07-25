#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetRNNAlgorithmDescriptor(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnAlgorithmDescriptor_t algoDesc)
{
	cudnnStatus_t retval = cudnnSetRNNAlgorithmDescriptor(handle, rnnDesc, algoDesc);
	return retval;
}