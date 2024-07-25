#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateRNNDescriptor(cudnnRNNDescriptor_t *rnnDesc)
{
	cudnnStatus_t retval = cudnnCreateRNNDescriptor(rnnDesc);
	return retval;
}