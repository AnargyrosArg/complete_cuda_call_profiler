#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetFilter4dDescriptor(cudnnFilterDescriptor_t filterDesc, cudnnDataType_t dataType, cudnnTensorFormat_t format, int k, int c, int h, int w)
{
	cudnnStatus_t retval = cudnnSetFilter4dDescriptor(filterDesc, dataType, format, k, c, h, w);
	return retval;
}