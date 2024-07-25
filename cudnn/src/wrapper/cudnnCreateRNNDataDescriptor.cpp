#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateRNNDataDescriptor(cudnnRNNDataDescriptor_t *rnnDataDesc)
{
	cudnnStatus_t retval = cudnnCreateRNNDataDescriptor(rnnDataDesc);
	return retval;
}