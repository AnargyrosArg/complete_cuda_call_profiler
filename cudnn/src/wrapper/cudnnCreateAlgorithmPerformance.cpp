#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreateAlgorithmPerformance(cudnnAlgorithmPerformance_t *algoPerf, int numberToCreate)
{
	cudnnStatus_t retval = cudnnCreateAlgorithmPerformance(algoPerf, numberToCreate);
	return retval;
}