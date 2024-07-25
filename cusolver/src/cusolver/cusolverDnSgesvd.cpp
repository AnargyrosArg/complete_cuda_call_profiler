#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgesvd)(cusolverDnHandle_t, signed char, signed char, int, int, float *, int, float *, float *, int, float *, int, float *, int, float *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgesvd(cusolverDnHandle_t handle, signed char jobu, signed char jobvt, int m, int n, float *A, int lda, float *S, float *U, int ldu, float *VT, int ldvt, float *work, int lwork, float *rwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgesvd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgesvd = (cusolverStatus_t (*)(cusolverDnHandle_t, signed char, signed char, int, int, float *, int, float *, float *, int, float *, int, float *, int, float *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgesvd");
			fprintf(stderr, "wrapper_cusolverDnSgesvd:%p\n", wrapper_cusolverDnSgesvd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgesvd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgesvd(handle, jobu, jobvt, m, n, A, lda, S, U, ldu, VT, ldvt, work, lwork, rwork, info);
		return retval;
	}
}