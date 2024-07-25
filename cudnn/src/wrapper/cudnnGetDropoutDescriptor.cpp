#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetDropoutDescriptor(cudnnDropoutDescriptor_t dropoutDesc, cudnnHandle_t handle, float *dropout, void **states, unsigned long long *seed)
{
	cudnnStatus_t retval = cudnnGetDropoutDescriptor(dropoutDesc, handle, dropout, states, seed);
	return retval;
}