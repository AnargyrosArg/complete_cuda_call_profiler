#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyCTCLossDescriptor(cudnnCTCLossDescriptor_t ctcLossDesc)
{
	cudnnStatus_t retval = cudnnDestroyCTCLossDescriptor(ctcLossDesc);
	return retval;
}