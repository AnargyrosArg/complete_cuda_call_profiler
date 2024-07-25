#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZYgels)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, void *, size_t, cusolver_int_t *, cusolver_int_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZYgels(cusolverDnHandle_t handle, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, cuDoubleComplex *dA, cusolver_int_t ldda, cuDoubleComplex *dB, cusolver_int_t lddb, cuDoubleComplex *dX, cusolver_int_t lddx, void *dWorkspace, size_t lwork_bytes, cusolver_int_t *iter, cusolver_int_t *d_info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZYgels)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZYgels = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, cuDoubleComplex *, cusolver_int_t, void *, size_t, cusolver_int_t *, cusolver_int_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZYgels");
			fprintf(stderr, "wrapper_cusolverDnZYgels:%p\n", wrapper_cusolverDnZYgels);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZYgels():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZYgels(handle, m, n, nrhs, dA, ldda, dB, lddb, dX, lddx, dWorkspace, lwork_bytes, iter, d_info);
		return retval;
	}
}