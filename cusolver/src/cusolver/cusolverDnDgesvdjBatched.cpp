#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgesvdjBatched)(cusolverDnHandle_t, cusolverEigMode_t, int, int, double *, int, double *, double *, int, double *, int, double *, int, int *, gesvdjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgesvdjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, double *A, int lda, double *S, double *U, int ldu, double *V, int ldv, double *work, int lwork, int *info, gesvdjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgesvdjBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgesvdjBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, double *, int, double *, double *, int, double *, int, double *, int, int *, gesvdjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgesvdjBatched");
			fprintf(stderr, "wrapper_cusolverDnDgesvdjBatched:%p\n", wrapper_cusolverDnDgesvdjBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgesvdjBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgesvdjBatched(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params, batchSize);
		return retval;
	}
}