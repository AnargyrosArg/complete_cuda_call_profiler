#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyPoolingDescriptor(cudnnPoolingDescriptor_t poolingDesc)
{
	cudnnStatus_t retval = cudnnDestroyPoolingDescriptor(poolingDesc);
	return retval;
}