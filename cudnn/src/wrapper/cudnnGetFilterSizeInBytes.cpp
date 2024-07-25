#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetFilterSizeInBytes(const cudnnFilterDescriptor_t filterDesc, size_t *size)
{
	cudnnStatus_t retval = cudnnGetFilterSizeInBytes(filterDesc, size);
	return retval;
}