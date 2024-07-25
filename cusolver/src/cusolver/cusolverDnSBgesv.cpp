#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSBgesv)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, float *, cusolver_int_t, cusolver_int_t *, float *, cusolver_int_t, float *, cusolver_int_t, void *, size_t, cusolver_int_t *, cusolver_int_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSBgesv(cusolverDnHandle_t handle, cusolver_int_t n, cusolver_int_t nrhs, float *dA, cusolver_int_t ldda, cusolver_int_t *dipiv, float *dB, cusolver_int_t lddb, float *dX, cusolver_int_t lddx, void *dWorkspace, size_t lwork_bytes, cusolver_int_t *iter, cusolver_int_t *d_info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSBgesv)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSBgesv = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, float *, cusolver_int_t, cusolver_int_t *, float *, cusolver_int_t, float *, cusolver_int_t, void *, size_t, cusolver_int_t *, cusolver_int_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSBgesv");
			fprintf(stderr, "wrapper_cusolverDnSBgesv:%p\n", wrapper_cusolverDnSBgesv);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSBgesv():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSBgesv(handle, n, nrhs, dA, ldda, dipiv, dB, lddb, dX, lddx, dWorkspace, lwork_bytes, iter, d_info);
		return retval;
	}
}