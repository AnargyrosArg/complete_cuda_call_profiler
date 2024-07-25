#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateOpTensorDescriptor(cudnnOpTensorDescriptor_t *opTensorDesc)
{
	cudnnStatus_t retval = cudnnCreateOpTensorDescriptor(opTensorDesc);
	return retval;
}