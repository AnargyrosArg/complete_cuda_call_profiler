#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetRNNParamsSize(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const cudnnTensorDescriptor_t xDesc, size_t *sizeInBytes, cudnnDataType_t dataType)
{
	cudnnStatus_t retval = cudnnGetRNNParamsSize(handle, rnnDesc, xDesc, sizeInBytes, dataType);
	return retval;
}