#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSSgels_bufferSize)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, float *, cusolver_int_t, float *, cusolver_int_t, float *, cusolver_int_t, void *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSSgels_bufferSize(cusolverDnHandle_t handle, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, float *dA, cusolver_int_t ldda, float *dB, cusolver_int_t lddb, float *dX, cusolver_int_t lddx, void *dWorkspace, size_t *lwork_bytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSSgels_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSSgels_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, float *, cusolver_int_t, float *, cusolver_int_t, float *, cusolver_int_t, void *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSSgels_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSSgels_bufferSize:%p\n", wrapper_cusolverDnSSgels_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSSgels_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSSgels_bufferSize(handle, m, n, nrhs, dA, ldda, dB, lddb, dX, lddx, dWorkspace, lwork_bytes);
		return retval;
	}
}