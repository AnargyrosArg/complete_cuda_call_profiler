#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSpotrfBatched)(cusolverDnHandle_t, cublasFillMode_t, int, float **, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSpotrfBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *Aarray[], int lda, int *infoArray, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSpotrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSpotrfBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float **, int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSpotrfBatched");
			fprintf(stderr, "wrapper_cusolverDnSpotrfBatched:%p\n", wrapper_cusolverDnSpotrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSpotrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSpotrfBatched(handle, uplo, n, Aarray, lda, infoArray, batchSize);
		return retval;
	}
}