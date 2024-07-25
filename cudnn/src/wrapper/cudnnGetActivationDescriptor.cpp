#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetActivationDescriptor(const cudnnActivationDescriptor_t activationDesc, cudnnActivationMode_t *mode, cudnnNanPropagation_t *reluNanOpt, double *coef)
{
	cudnnStatus_t retval = cudnnGetActivationDescriptor(activationDesc, mode, reluNanOpt, coef);
	return retval;
}