#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnChegvj_bufferSize)(cusolverDnHandle_t, cusolverEigType_t, cusolverEigMode_t, cublasFillMode_t, int, const cuComplex *, int, const cuComplex *, int, const float *, int *, syevjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnChegvj_bufferSize(cusolverDnHandle_t handle, cusolverEigType_t itype, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, const cuComplex *B, int ldb, const float *W, int *lwork, syevjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnChegvj_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnChegvj_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigType_t, cusolverEigMode_t, cublasFillMode_t, int, const cuComplex *, int, const cuComplex *, int, const float *, int *, syevjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnChegvj_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnChegvj_bufferSize:%p\n", wrapper_cusolverDnChegvj_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnChegvj_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnChegvj_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, W, lwork, params);
		return retval;
	}
}