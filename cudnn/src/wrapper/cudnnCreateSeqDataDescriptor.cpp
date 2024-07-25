#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateSeqDataDescriptor(cudnnSeqDataDescriptor_t *seqDataDesc)
{
	cudnnStatus_t retval = cudnnCreateSeqDataDescriptor(seqDataDesc);
	return retval;
}