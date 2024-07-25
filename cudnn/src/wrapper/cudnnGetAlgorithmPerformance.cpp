#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetAlgorithmPerformance(const cudnnAlgorithmPerformance_t algoPerf, cudnnAlgorithmDescriptor_t *algoDesc, cudnnStatus_t *status, float *time, size_t *memory)
{
	cudnnStatus_t retval = cudnnGetAlgorithmPerformance(algoPerf, algoDesc, status, time, memory);
	return retval;
}