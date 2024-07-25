#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetCTCLossDescriptor_v8(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t *compType, cudnnLossNormalizationMode_t *normMode, cudnnNanPropagation_t *gradMode, int *maxLabelLength)
{
	cudnnStatus_t retval = cudnnGetCTCLossDescriptor_v8(ctcLossDesc, compType, normMode, gradMode, maxLabelLength);
	return retval;
}