#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnMakeFusedOpsPlan(cudnnHandle_t handle, cudnnFusedOpsPlan_t plan, const cudnnFusedOpsConstParamPack_t constPack, size_t *workspaceSizeInBytes)
{
	cudnnStatus_t retval = cudnnMakeFusedOpsPlan(handle, plan, constPack, workspaceSizeInBytes);
	return retval;
}