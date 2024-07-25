#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyFusedOpsVariantParamPack(cudnnFusedOpsVariantParamPack_t varPack)
{
	cudnnStatus_t retval = cudnnDestroyFusedOpsVariantParamPack(varPack);
	return retval;
}