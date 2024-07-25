#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetRNNProjectionLayers(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, const int recProjSize, const int outProjSize)
{
	cudnnStatus_t retval = cudnnSetRNNProjectionLayers(handle, rnnDesc, recProjSize, outProjSize);
	return retval;
}