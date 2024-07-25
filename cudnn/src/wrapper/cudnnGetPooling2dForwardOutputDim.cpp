#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetPooling2dForwardOutputDim(const cudnnPoolingDescriptor_t poolingDesc, const cudnnTensorDescriptor_t inputTensorDesc, int *n, int *c, int *h, int *w)
{
	cudnnStatus_t retval = cudnnGetPooling2dForwardOutputDim(poolingDesc, inputTensorDesc, n, c, h, w);
	return retval;
}