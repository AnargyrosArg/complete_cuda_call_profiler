#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnOpsTrainVersionCheck()
{
	cudnnStatus_t retval = cudnnOpsTrainVersionCheck();
	return retval;
}