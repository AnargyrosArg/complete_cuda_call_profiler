#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgesvd)(cusolverDnHandle_t, signed char, signed char, int, int, double *, int, double *, double *, int, double *, int, double *, int, double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgesvd(cusolverDnHandle_t handle, signed char jobu, signed char jobvt, int m, int n, double *A, int lda, double *S, double *U, int ldu, double *VT, int ldvt, double *work, int lwork, double *rwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgesvd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgesvd = (cusolverStatus_t (*)(cusolverDnHandle_t, signed char, signed char, int, int, double *, int, double *, double *, int, double *, int, double *, int, double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgesvd");
			fprintf(stderr, "wrapper_cusolverDnDgesvd:%p\n", wrapper_cusolverDnDgesvd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgesvd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgesvd(handle, jobu, jobvt, m, n, A, lda, S, U, ldu, VT, ldvt, work, lwork, rwork, info);
		return retval;
	}
}