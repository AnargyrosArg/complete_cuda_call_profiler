#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetRNNProjectionLayers(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *recProjSize, int *outProjSize)
{
	cudnnStatus_t retval = cudnnGetRNNProjectionLayers(handle, rnnDesc, recProjSize, outProjSize);
	return retval;
}