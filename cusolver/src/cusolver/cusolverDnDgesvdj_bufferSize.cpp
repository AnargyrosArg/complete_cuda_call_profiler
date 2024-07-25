#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgesvdj_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const double *, int, const double *, const double *, int, const double *, int, int *, gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgesvdj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, const double *A, int lda, const double *S, const double *U, int ldu, const double *V, int ldv, int *lwork, gesvdjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgesvdj_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgesvdj_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const double *, int, const double *, const double *, int, const double *, int, int *, gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgesvdj_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDgesvdj_bufferSize:%p\n", wrapper_cusolverDnDgesvdj_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgesvdj_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgesvdj_bufferSize(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, lwork, params);
		return retval;
	}
}