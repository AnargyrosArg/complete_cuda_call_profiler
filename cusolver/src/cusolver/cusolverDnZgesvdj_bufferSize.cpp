#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgesvdj_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const cuDoubleComplex *, int, const double *, const cuDoubleComplex *, int, const cuDoubleComplex *, int, int *, gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgesvdj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, const cuDoubleComplex *A, int lda, const double *S, const cuDoubleComplex *U, int ldu, const cuDoubleComplex *V, int ldv, int *lwork, gesvdjInfo_t params) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgesvdj_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgesvdj_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const cuDoubleComplex *, int, const double *, const cuDoubleComplex *, int, const cuDoubleComplex *, int, int *, gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgesvdj_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZgesvdj_bufferSize:%p\n", wrapper_cusolverDnZgesvdj_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgesvdj_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgesvdj_bufferSize(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, lwork, params);
		return retval;
	}
}