#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetWorkspace_v2(cublasHandle_t handle, void *workspace, size_t workspaceSizeInBytes)
{
	cublasStatus_t retval = cublasSetWorkspace_v2(handle, workspace, workspaceSizeInBytes);
	return retval;
}