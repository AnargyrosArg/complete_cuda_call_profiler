#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXtrtri_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, cublasDiagType_t, int64_t, cudaDataType, void *, int64_t, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXtrtri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, cublasDiagType_t diag, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXtrtri_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXtrtri_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, cublasDiagType_t, int64_t, cudaDataType, void *, int64_t, size_t *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXtrtri_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnXtrtri_bufferSize:%p\n", wrapper_cusolverDnXtrtri_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXtrtri_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXtrtri_bufferSize(handle, uplo, diag, n, dataTypeA, A, lda, workspaceInBytesOnDevice, workspaceInBytesOnHost);
		return retval;
	}
}