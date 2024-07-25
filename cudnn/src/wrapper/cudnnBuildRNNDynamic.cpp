#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnBuildRNNDynamic(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, int miniBatch)
{
	cudnnStatus_t retval = cudnnBuildRNNDynamic(handle, rnnDesc, miniBatch);
	return retval;
}