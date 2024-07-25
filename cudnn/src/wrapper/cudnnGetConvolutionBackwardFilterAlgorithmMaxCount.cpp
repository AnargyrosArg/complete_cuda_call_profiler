#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount(cudnnHandle_t handle, int *count)
{
	cudnnStatus_t retval = cudnnGetConvolutionBackwardFilterAlgorithmMaxCount(handle, count);
	return retval;
}