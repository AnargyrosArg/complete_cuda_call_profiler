#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetConvolutionReorderType(cudnnConvolutionDescriptor_t convDesc, cudnnReorderType_t *reorderType)
{
	cudnnStatus_t retval = cudnnGetConvolutionReorderType(convDesc, reorderType);
	return retval;
}