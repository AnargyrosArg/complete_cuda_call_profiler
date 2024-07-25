#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnIm2Col(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnFilterDescriptor_t wDesc, const cudnnConvolutionDescriptor_t convDesc, void *colBuffer)
{
	cudnnStatus_t retval = cudnnIm2Col(handle, xDesc, x, wDesc, convDesc, colBuffer);
	return retval;
}