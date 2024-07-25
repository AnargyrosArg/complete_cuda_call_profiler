#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgesvdjBatched_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, int, int, const cuComplex *, int, const float *, const cuComplex *, int, const cuComplex *, int, int *, gesvdjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgesvdjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, const cuComplex *A, int lda, const float *S, const cuComplex *U, int ldu, const cuComplex *V, int ldv, int *lwork, gesvdjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgesvdjBatched_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgesvdjBatched_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, const cuComplex *, int, const float *, const cuComplex *, int, const cuComplex *, int, int *, gesvdjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgesvdjBatched_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCgesvdjBatched_bufferSize:%p\n", wrapper_cusolverDnCgesvdjBatched_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgesvdjBatched_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgesvdjBatched_bufferSize(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, lwork, params, batchSize);
		return retval;
	}
}