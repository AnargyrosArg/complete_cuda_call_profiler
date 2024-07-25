#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetCallback(unsigned *mask, void **udata, cudnnCallback_t *fptr)
{
	cudnnStatus_t retval = cudnnGetCallback(mask, udata, fptr);
	return retval;
}