#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnFusedOpsExecute(cudnnHandle_t handle, const cudnnFusedOpsPlan_t plan, cudnnFusedOpsVariantParamPack_t varPack)
{
	cudnnStatus_t retval = cudnnFusedOpsExecute(handle, plan, varPack);
	return retval;
}