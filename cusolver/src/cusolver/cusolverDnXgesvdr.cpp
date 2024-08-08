#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvdr)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, int64_t, int64_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, size_t, void *, size_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvdr(cusolverDnHandle_t handle, cusolverDnParams_t params, signed char jobu, signed char jobv, int64_t m, int64_t n, int64_t k, int64_t p, int64_t niters, cudaDataType dataTypeA, void *A, int64_t lda, cudaDataType dataTypeSrand, void *Srand, cudaDataType dataTypeUrand, void *Urand, int64_t ldUrand, cudaDataType dataTypeVrand, void *Vrand, int64_t ldVrand, cudaDataType computeType, void *bufferOnDevice, size_t workspaceInBytesOnDevice, void *bufferOnHost, size_t workspaceInBytesOnHost, int *d_info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvdr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvdr = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, int64_t, int64_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, size_t, void *, size_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvdr");
			fprintf(stderr, "wrapper_cusolverDnXgesvdr:%p\n", wrapper_cusolverDnXgesvdr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvdr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvdr(handle, params, jobu, jobv, m, n, k, p, niters, dataTypeA, A, lda, dataTypeSrand, Srand, dataTypeUrand, Urand, ldUrand, dataTypeVrand, Vrand, ldVrand, computeType, bufferOnDevice, workspaceInBytesOnDevice, bufferOnHost, workspaceInBytesOnHost, d_info);
		return retval;
	}
}