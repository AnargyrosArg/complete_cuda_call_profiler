#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgesvdjBatched_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, int, int, const double *, int, const double *, const double *, int, const double *, int, int *, gesvdjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgesvdjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, const double *A, int lda, const double *S, const double *U, int ldu, const double *V, int ldv, int *lwork, gesvdjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgesvdjBatched_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgesvdjBatched_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, const double *, int, const double *, const double *, int, const double *, int, int *, gesvdjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgesvdjBatched_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDgesvdjBatched_bufferSize:%p\n", wrapper_cusolverDnDgesvdjBatched_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgesvdjBatched_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgesvdjBatched_bufferSize(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, lwork, params, batchSize);
		return retval;
	}
}