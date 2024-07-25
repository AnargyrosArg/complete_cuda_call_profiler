#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetCTCLossDescriptor(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t compType)
{
	cudnnStatus_t retval = cudnnSetCTCLossDescriptor(ctcLossDesc, compType);
	return retval;
}