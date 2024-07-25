#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateAttnDescriptor(cudnnAttnDescriptor_t *attnDesc)
{
	cudnnStatus_t retval = cudnnCreateAttnDescriptor(attnDesc);
	return retval;
}