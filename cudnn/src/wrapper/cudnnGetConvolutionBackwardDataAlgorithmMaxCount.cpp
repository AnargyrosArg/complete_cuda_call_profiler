#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount(cudnnHandle_t handle, int *count)
{
	cudnnStatus_t retval = cudnnGetConvolutionBackwardDataAlgorithmMaxCount(handle, count);
	return retval;
}