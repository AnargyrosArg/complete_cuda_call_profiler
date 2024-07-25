#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyAlgorithmPerformance(cudnnAlgorithmPerformance_t *algoPerf, int numberToDestroy)
{
	cudnnStatus_t retval = cudnnDestroyAlgorithmPerformance(algoPerf, numberToDestroy);
	return retval;
}