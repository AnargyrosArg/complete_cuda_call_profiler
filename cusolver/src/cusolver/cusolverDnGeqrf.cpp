#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnGeqrf)(cusolverDnHandle_t, cusolverDnParams_t, int64_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, size_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnGeqrf(cusolverDnHandle_t handle, cusolverDnParams_t params, int64_t m, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, cudaDataType dataTypeTau, void *tau, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnGeqrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnGeqrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, int64_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, size_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnGeqrf");
			fprintf(stderr, "wrapper_cusolverDnGeqrf:%p\n", wrapper_cusolverDnGeqrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnGeqrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnGeqrf(handle, params, m, n, dataTypeA, A, lda, dataTypeTau, tau, computeType, pBuffer, workspaceInBytes, info);
		return retval;
	}
}