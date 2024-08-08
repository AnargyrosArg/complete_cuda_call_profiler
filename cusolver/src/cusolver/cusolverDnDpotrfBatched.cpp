#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDpotrfBatched)(cusolverDnHandle_t, cublasFillMode_t, int, double **, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDpotrfBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *Aarray[], int lda, int *infoArray, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDpotrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDpotrfBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double **, int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDpotrfBatched");
			fprintf(stderr, "wrapper_cusolverDnDpotrfBatched:%p\n", wrapper_cusolverDnDpotrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDpotrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDpotrfBatched(handle, uplo, n, Aarray, lda, infoArray, batchSize);
		return retval;
	}
}