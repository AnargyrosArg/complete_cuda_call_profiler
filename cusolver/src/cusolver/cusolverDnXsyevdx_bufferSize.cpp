#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsyevdx_bufferSize)(cusolverDnHandle_t, cusolverDnParams_t, cusolverEigMode_t, cusolverEigRange_t, cublasFillMode_t, int64_t, cudaDataType, const void *, int64_t, void *, void *, int64_t, int64_t, int64_t *, cudaDataType, const void *, cudaDataType, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsyevdx_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, void *vl, void *vu, int64_t il, int64_t iu, int64_t *h_meig, cudaDataType dataTypeW, const void *W, cudaDataType computeType, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsyevdx_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsyevdx_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, cusolverEigMode_t, cusolverEigRange_t, cublasFillMode_t, int64_t, cudaDataType, const void *, int64_t, void *, void *, int64_t, int64_t, int64_t *, cudaDataType, const void *, cudaDataType, size_t *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsyevdx_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnXsyevdx_bufferSize:%p\n", wrapper_cusolverDnXsyevdx_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsyevdx_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsyevdx_bufferSize(handle, params, jobz, range, uplo, n, dataTypeA, A, lda, vl, vu, il, iu, h_meig, dataTypeW, W, computeType, workspaceInBytesOnDevice, workspaceInBytesOnHost);
		return retval;
	}
}