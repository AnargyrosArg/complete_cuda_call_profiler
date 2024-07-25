#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateConvolutionDescriptor(cudnnConvolutionDescriptor_t *convDesc)
{
	cudnnStatus_t retval = cudnnCreateConvolutionDescriptor(convDesc);
	return retval;
}