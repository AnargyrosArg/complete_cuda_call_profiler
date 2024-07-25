#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZZgesv_bufferSize)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, cusolver_int_t *, cuDoubleComplex *, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, void *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZZgesv_bufferSize(cusolverDnHandle_t handle, cusolver_int_t n, cusolver_int_t nrhs, cuDoubleComplex *dA, cusolver_int_t ldda, cusolver_int_t *dipiv, cuDoubleComplex *dB, cusolver_int_t lddb, cuDoubleComplex *dX, cusolver_int_t lddx, void *dWorkspace, size_t *lwork_bytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZZgesv_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZZgesv_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, cusolver_int_t *, cuDoubleComplex *, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, void *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZZgesv_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZZgesv_bufferSize:%p\n", wrapper_cusolverDnZZgesv_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZZgesv_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZZgesv_bufferSize(handle, n, nrhs, dA, ldda, dipiv, dB, lddb, dX, lddx, dWorkspace, lwork_bytes);
		return retval;
	}
}