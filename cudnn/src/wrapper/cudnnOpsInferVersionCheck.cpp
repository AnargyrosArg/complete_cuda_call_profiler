#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnOpsInferVersionCheck()
{
	cudnnStatus_t retval = cudnnOpsInferVersionCheck();
	return retval;
}