#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetCTCLossDescriptorEx(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t *compType, cudnnLossNormalizationMode_t *normMode, cudnnNanPropagation_t *gradMode)
{
	cudnnStatus_t retval = cudnnGetCTCLossDescriptorEx(ctcLossDesc, compType, normMode, gradMode);
	return retval;
}