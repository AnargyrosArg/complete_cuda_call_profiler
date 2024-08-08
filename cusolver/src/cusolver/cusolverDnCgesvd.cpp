#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgesvd)(cusolverDnHandle_t, signed char, signed char, int, int, cuComplex *, int, float *, cuComplex *, int, cuComplex *, int, cuComplex *, int, float *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgesvd(cusolverDnHandle_t handle, signed char jobu, signed char jobvt, int m, int n, cuComplex *A, int lda, float *S, cuComplex *U, int ldu, cuComplex *VT, int ldvt, cuComplex *work, int lwork, float *rwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgesvd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgesvd = (cusolverStatus_t (*)(cusolverDnHandle_t, signed char, signed char, int, int, cuComplex *, int, float *, cuComplex *, int, cuComplex *, int, cuComplex *, int, float *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgesvd");
			fprintf(stderr, "wrapper_cusolverDnCgesvd:%p\n", wrapper_cusolverDnCgesvd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgesvd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgesvd(handle, jobu, jobvt, m, n, A, lda, S, U, ldu, VT, ldvt, work, lwork, rwork, info);
		return retval;
	}
}