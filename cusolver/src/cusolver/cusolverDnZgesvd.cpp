#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgesvd)(cusolverDnHandle_t, signed char, signed char, int, int, cuDoubleComplex *, int, double *, cuDoubleComplex *, int, cuDoubleComplex *, int, cuDoubleComplex *, int, double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgesvd(cusolverDnHandle_t handle, signed char jobu, signed char jobvt, int m, int n, cuDoubleComplex *A, int lda, double *S, cuDoubleComplex *U, int ldu, cuDoubleComplex *VT, int ldvt, cuDoubleComplex *work, int lwork, double *rwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgesvd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgesvd = (cusolverStatus_t (*)(cusolverDnHandle_t, signed char, signed char, int, int, cuDoubleComplex *, int, double *, cuDoubleComplex *, int, cuDoubleComplex *, int, cuDoubleComplex *, int, double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgesvd");
			fprintf(stderr, "wrapper_cusolverDnZgesvd:%p\n", wrapper_cusolverDnZgesvd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgesvd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgesvd(handle, jobu, jobvt, m, n, A, lda, S, U, ldu, VT, ldvt, work, lwork, rwork, info);
		return retval;
	}
}