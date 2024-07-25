#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnReduceTensor(cudnnHandle_t handle, const cudnnReduceTensorDescriptor_t reduceTensorDesc, void *indices, size_t indicesSizeInBytes, void *workspace, size_t workspaceSizeInBytes, const void *alpha, const cudnnTensorDescriptor_t aDesc, const void *A, const void *beta, const cudnnTensorDescriptor_t cDesc, void *C)
{
	cudnnStatus_t retval = cudnnReduceTensor(handle, reduceTensorDesc, indices, indicesSizeInBytes, workspace, workspaceSizeInBytes, alpha, aDesc, A, beta, cDesc, C);
	return retval;
}