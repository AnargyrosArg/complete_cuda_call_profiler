#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDDgels)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, double *, cusolver_int_t, double *, cusolver_int_t, double *, cusolver_int_t, void *, size_t, cusolver_int_t *, cusolver_int_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDDgels(cusolverDnHandle_t handle, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, double *dA, cusolver_int_t ldda, double *dB, cusolver_int_t lddb, double *dX, cusolver_int_t lddx, void *dWorkspace, size_t lwork_bytes, cusolver_int_t *iter, cusolver_int_t *d_info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDDgels)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDDgels = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, double *, cusolver_int_t, double *, cusolver_int_t, double *, cusolver_int_t, void *, size_t, cusolver_int_t *, cusolver_int_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDDgels");
			fprintf(stderr, "wrapper_cusolverDnDDgels:%p\n", wrapper_cusolverDnDDgels);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDDgels():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDDgels(handle, m, n, nrhs, dA, ldda, dB, lddb, dX, lddx, dWorkspace, lwork_bytes, iter, d_info);
		return retval;
	}
}