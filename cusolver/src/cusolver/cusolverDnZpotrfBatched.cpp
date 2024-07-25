#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZpotrfBatched)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex **, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZpotrfBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *Aarray[], int lda, int *infoArray, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZpotrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZpotrfBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex **, int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZpotrfBatched");
			fprintf(stderr, "wrapper_cusolverDnZpotrfBatched:%p\n", wrapper_cusolverDnZpotrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZpotrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZpotrfBatched(handle, uplo, n, Aarray, lda, infoArray, batchSize);
		return retval;
	}
}