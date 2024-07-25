#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetProperty(libraryPropertyType type, int *value)
{
	cudnnStatus_t retval = cudnnGetProperty(type, value);
	return retval;
}