#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnRNNBackwardWeightsEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const cudnnRNNDataDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnRNNDataDescriptor_t yDesc, const void *y, void *workSpace, size_t workSpaceSizeInBytes, const cudnnFilterDescriptor_t dwDesc, void *dw, void *reserveSpace, size_t reserveSpaceSizeInBytes)
{
	cudnnStatus_t retval = cudnnRNNBackwardWeightsEx(handle, rnnDesc, xDesc, x, hxDesc, hx, yDesc, y, workSpace, workSpaceSizeInBytes, dwDesc, dw, reserveSpace, reserveSpaceSizeInBytes);
	return retval;
}