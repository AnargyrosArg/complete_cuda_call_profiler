#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnAdvTrainVersionCheck()
{
	cudnnStatus_t retval = cudnnAdvTrainVersionCheck();
	return retval;
}