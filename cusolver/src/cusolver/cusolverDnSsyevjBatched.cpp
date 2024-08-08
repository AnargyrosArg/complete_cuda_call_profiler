#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsyevjBatched)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, float *, int, float *, float *, int, int *, syevjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsyevjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, float *A, int lda, float *W, float *work, int lwork, int *info, syevjInfo_t params, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsyevjBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsyevjBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, float *, int, float *, float *, int, int *, syevjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsyevjBatched");
			fprintf(stderr, "wrapper_cusolverDnSsyevjBatched:%p\n", wrapper_cusolverDnSsyevjBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsyevjBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsyevjBatched(handle, jobz, uplo, n, A, lda, W, work, lwork, info, params, batchSize);
		return retval;
	}
}