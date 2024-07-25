#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetFusedOpsVariantParamPackAttribute(const cudnnFusedOpsVariantParamPack_t varPack, cudnnFusedOpsVariantParamLabel_t paramLabel, void *ptr)
{
	cudnnStatus_t retval = cudnnGetFusedOpsVariantParamPackAttribute(varPack, paramLabel, ptr);
	return retval;
}