#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgesvdj)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, float *, int, float *, float *, int, float *, int, float *, int, int *, gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgesvdj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, float *A, int lda, float *S, float *U, int ldu, float *V, int ldv, float *work, int lwork, int *info, gesvdjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgesvdj)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgesvdj = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, float *, int, float *, float *, int, float *, int, float *, int, int *, gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgesvdj");
			fprintf(stderr, "wrapper_cusolverDnSgesvdj:%p\n", wrapper_cusolverDnSgesvdj);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgesvdj():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgesvdj(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params);
		return retval;
	}
}