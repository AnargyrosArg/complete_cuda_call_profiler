#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgesvdj_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const cuComplex *, int, const float *, const cuComplex *, int, const cuComplex *, int, int *, gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgesvdj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, const cuComplex *A, int lda, const float *S, const cuComplex *U, int ldu, const cuComplex *V, int ldv, int *lwork, gesvdjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgesvdj_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgesvdj_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const cuComplex *, int, const float *, const cuComplex *, int, const cuComplex *, int, int *, gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgesvdj_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCgesvdj_bufferSize:%p\n", wrapper_cusolverDnCgesvdj_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgesvdj_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgesvdj_bufferSize(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, lwork, params);
		return retval;
	}
}