#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetAlgorithmPerformance(cudnnAlgorithmPerformance_t algoPerf, cudnnAlgorithmDescriptor_t algoDesc, cudnnStatus_t status, float time, size_t memory)
{
	cudnnStatus_t retval = cudnnSetAlgorithmPerformance(algoPerf, algoDesc, status, time, memory);
	return retval;
}