#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgesvdaStridedBatched_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const float *, int, long long int, const float *, long long int, const float *, int, long long int, const float *, int, long long int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgesvdaStridedBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int rank, int m, int n, const float *d_A, int lda, long long int strideA, const float *d_S, long long int strideS, const float *d_U, int ldu, long long int strideU, const float *d_V, int ldv, long long int strideV, int *lwork, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgesvdaStridedBatched_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgesvdaStridedBatched_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const float *, int, long long int, const float *, long long int, const float *, int, long long int, const float *, int, long long int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgesvdaStridedBatched_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSgesvdaStridedBatched_bufferSize:%p\n", wrapper_cusolverDnSgesvdaStridedBatched_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgesvdaStridedBatched_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgesvdaStridedBatched_bufferSize(handle, jobz, rank, m, n, d_A, lda, strideA, d_S, strideS, d_U, ldu, strideU, d_V, ldv, strideV, lwork, batchSize);
		return retval;
	}
}