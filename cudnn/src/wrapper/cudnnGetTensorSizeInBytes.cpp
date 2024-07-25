#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetTensorSizeInBytes(const cudnnTensorDescriptor_t tensorDesc, size_t *size)
{
	cudnnStatus_t retval = cudnnGetTensorSizeInBytes(tensorDesc, size);
	return retval;
}