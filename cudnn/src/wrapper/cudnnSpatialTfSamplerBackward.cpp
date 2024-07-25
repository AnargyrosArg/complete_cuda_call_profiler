#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSpatialTfSamplerBackward(cudnnHandle_t handle, cudnnSpatialTransformerDescriptor_t stDesc, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *beta, const cudnnTensorDescriptor_t dxDesc, void *dx, const void *alphaDgrid, const cudnnTensorDescriptor_t dyDesc, const void *dy, const void *grid, const void *betaDgrid, void *dgrid)
{
	cudnnStatus_t retval = cudnnSpatialTfSamplerBackward(handle, stDesc, alpha, xDesc, x, beta, dxDesc, dx, alphaDgrid, dyDesc, dy, grid, betaDgrid, dgrid);
	return retval;
}