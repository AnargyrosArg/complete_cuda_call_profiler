#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnConvolutionBackwardBias(cudnnHandle_t handle, const void *alpha, const cudnnTensorDescriptor_t dyDesc, const void *dy, const void *beta, const cudnnTensorDescriptor_t dbDesc, void *db)
{
	cudnnStatus_t retval = cudnnConvolutionBackwardBias(handle, alpha, dyDesc, dy, beta, dbDesc, db);
	return retval;
}