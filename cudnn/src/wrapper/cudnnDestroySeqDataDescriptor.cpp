#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroySeqDataDescriptor(cudnnSeqDataDescriptor_t seqDataDesc)
{
	cudnnStatus_t retval = cudnnDestroySeqDataDescriptor(seqDataDesc);
	return retval;
}