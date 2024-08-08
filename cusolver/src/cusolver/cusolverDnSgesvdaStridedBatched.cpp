#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgesvdaStridedBatched)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const float *, int, long long int, float *, long long int, float *, int, long long int, float *, int, long long int, float *, int, int *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgesvdaStridedBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int rank, int m, int n, const float *d_A, int lda, long long int strideA, float *d_S, long long int strideS, float *d_U, int ldu, long long int strideU, float *d_V, int ldv, long long int strideV, float *d_work, int lwork, int *d_info, double *h_R_nrmF, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgesvdaStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgesvdaStridedBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const float *, int, long long int, float *, long long int, float *, int, long long int, float *, int, long long int, float *, int, int *, double *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgesvdaStridedBatched");
			fprintf(stderr, "wrapper_cusolverDnSgesvdaStridedBatched:%p\n", wrapper_cusolverDnSgesvdaStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgesvdaStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgesvdaStridedBatched(handle, jobz, rank, m, n, d_A, lda, strideA, d_S, strideS, d_U, ldu, strideU, d_V, ldv, strideV, d_work, lwork, d_info, h_R_nrmF, batchSize);
		return retval;
	}
}