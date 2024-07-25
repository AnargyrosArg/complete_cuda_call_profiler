#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDXgesv_bufferSize)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, double *, cusolver_int_t, cusolver_int_t *, double *, cusolver_int_t, double *, cusolver_int_t, void *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDXgesv_bufferSize(cusolverDnHandle_t handle, cusolver_int_t n, cusolver_int_t nrhs, double *dA, cusolver_int_t ldda, cusolver_int_t *dipiv, double *dB, cusolver_int_t lddb, double *dX, cusolver_int_t lddx, void *dWorkspace, size_t *lwork_bytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDXgesv_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDXgesv_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, double *, cusolver_int_t, cusolver_int_t *, double *, cusolver_int_t, double *, cusolver_int_t, void *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDXgesv_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDXgesv_bufferSize:%p\n", wrapper_cusolverDnDXgesv_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDXgesv_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDXgesv_bufferSize(handle, n, nrhs, dA, ldda, dipiv, dB, lddb, dX, lddx, dWorkspace, lwork_bytes);
		return retval;
	}
}