#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsyevj_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const double *, int, const double *, int *, syevjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsyevj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const double *A, int lda, const double *W, int *lwork, syevjInfo_t params) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsyevj_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsyevj_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const double *, int, const double *, int *, syevjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsyevj_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDsyevj_bufferSize:%p\n", wrapper_cusolverDnDsyevj_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsyevj_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsyevj_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork, params);
		return retval;
	}
}