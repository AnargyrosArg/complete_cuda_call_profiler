#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSpotrsBatched)(cusolverDnHandle_t, cublasFillMode_t, int, int, float **, int, float **, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSpotrsBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, float *A[], int lda, float *B[], int ldb, int *d_info, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSpotrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSpotrsBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, int, float **, int, float **, int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSpotrsBatched");
			fprintf(stderr, "wrapper_cusolverDnSpotrsBatched:%p\n", wrapper_cusolverDnSpotrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSpotrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, d_info, batchSize);
		return retval;
	}
}