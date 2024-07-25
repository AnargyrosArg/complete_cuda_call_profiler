#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetRNNPaddingMode(cudnnRNNDescriptor_t rnnDesc, unsigned paddingMode)
{
	cudnnStatus_t retval = cudnnSetRNNPaddingMode(rnnDesc, paddingMode);
	return retval;
}