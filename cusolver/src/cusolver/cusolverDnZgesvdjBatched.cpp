#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgesvdjBatched)(cusolverDnHandle_t, cusolverEigMode_t, int, int, cuDoubleComplex *, int, double *, cuDoubleComplex *, int, cuDoubleComplex *, int, cuDoubleComplex *, int, int *, gesvdjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgesvdjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, cuDoubleComplex *A, int lda, double *S, cuDoubleComplex *U, int ldu, cuDoubleComplex *V, int ldv, cuDoubleComplex *work, int lwork, int *info, gesvdjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgesvdjBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgesvdjBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, cuDoubleComplex *, int, double *, cuDoubleComplex *, int, cuDoubleComplex *, int, cuDoubleComplex *, int, int *, gesvdjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgesvdjBatched");
			fprintf(stderr, "wrapper_cusolverDnZgesvdjBatched:%p\n", wrapper_cusolverDnZgesvdjBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgesvdjBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgesvdjBatched(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params, batchSize);
		return retval;
	}
}