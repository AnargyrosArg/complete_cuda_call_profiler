#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetFusedOpsVariantParamPackAttribute(cudnnFusedOpsVariantParamPack_t varPack, cudnnFusedOpsVariantParamLabel_t paramLabel, void *ptr)
{
	cudnnStatus_t retval = cudnnSetFusedOpsVariantParamPackAttribute(varPack, paramLabel, ptr);
	return retval;
}