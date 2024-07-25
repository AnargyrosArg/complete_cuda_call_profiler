#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDlauum)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDlauum(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *work, int lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDlauum)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDlauum = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDlauum");
			fprintf(stderr, "wrapper_cusolverDnDlauum:%p\n", wrapper_cusolverDnDlauum);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDlauum():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDlauum(handle, uplo, n, A, lda, work, lwork, devInfo);
		return retval;
	}
}