#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetActivationDescriptor(cudnnActivationDescriptor_t activationDesc, cudnnActivationMode_t mode, cudnnNanPropagation_t reluNanOpt, double coef)
{
	cudnnStatus_t retval = cudnnSetActivationDescriptor(activationDesc, mode, reluNanOpt, coef);
	return retval;
}