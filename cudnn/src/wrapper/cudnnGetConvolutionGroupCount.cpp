#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetConvolutionGroupCount(cudnnConvolutionDescriptor_t convDesc, int *groupCount)
{
	cudnnStatus_t retval = cudnnGetConvolutionGroupCount(convDesc, groupCount);
	return retval;
}