#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCheevjBatched)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, cuComplex *, int, float *, cuComplex *, int, int *, syevjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCheevjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuComplex *A, int lda, float *W, cuComplex *work, int lwork, int *info, syevjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCheevjBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCheevjBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, cuComplex *, int, float *, cuComplex *, int, int *, syevjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCheevjBatched");
			fprintf(stderr, "wrapper_cusolverDnCheevjBatched:%p\n", wrapper_cusolverDnCheevjBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCheevjBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCheevjBatched(handle, jobz, uplo, n, A, lda, W, work, lwork, info, params, batchSize);
		return retval;
	}
}