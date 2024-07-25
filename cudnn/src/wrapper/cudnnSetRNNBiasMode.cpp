#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetRNNBiasMode(cudnnRNNDescriptor_t rnnDesc, cudnnRNNBiasMode_t biasMode)
{
	cudnnStatus_t retval = cudnnSetRNNBiasMode(rnnDesc, biasMode);
	return retval;
}