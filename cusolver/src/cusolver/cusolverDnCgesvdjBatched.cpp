#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgesvdjBatched)(cusolverDnHandle_t, cusolverEigMode_t, int, int, cuComplex *, int, float *, cuComplex *, int, cuComplex *, int, cuComplex *, int, int *, gesvdjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgesvdjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, cuComplex *A, int lda, float *S, cuComplex *U, int ldu, cuComplex *V, int ldv, cuComplex *work, int lwork, int *info, gesvdjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgesvdjBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgesvdjBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, cuComplex *, int, float *, cuComplex *, int, cuComplex *, int, cuComplex *, int, int *, gesvdjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgesvdjBatched");
			fprintf(stderr, "wrapper_cusolverDnCgesvdjBatched:%p\n", wrapper_cusolverDnCgesvdjBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgesvdjBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgesvdjBatched(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params, batchSize);
		return retval;
	}
}