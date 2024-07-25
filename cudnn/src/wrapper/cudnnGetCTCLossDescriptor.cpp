#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetCTCLossDescriptor(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t *compType)
{
	cudnnStatus_t retval = cudnnGetCTCLossDescriptor(ctcLossDesc, compType);
	return retval;
}