#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSpotrf)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *Workspace, int Lwork, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSpotrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSpotrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSpotrf");
			fprintf(stderr, "wrapper_cusolverDnSpotrf:%p\n", wrapper_cusolverDnSpotrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSpotrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
		return retval;
	}
}