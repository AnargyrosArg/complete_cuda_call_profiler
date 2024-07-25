#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount(cudnnHandle_t handle, int *count)
{
	cudnnStatus_t retval = cudnnGetConvolutionForwardAlgorithmMaxCount(handle, count);
	return retval;
}