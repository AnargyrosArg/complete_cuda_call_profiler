#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetTensor4dDescriptor(cudnnTensorDescriptor_t tensorDesc, cudnnTensorFormat_t format, cudnnDataType_t dataType, int n, int c, int h, int w)
{
	cudnnStatus_t retval = cudnnSetTensor4dDescriptor(tensorDesc, format, dataType, n, c, h, w);
	return retval;
}