#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgesvdaStridedBatched)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const cuDoubleComplex *, int, long long int, double *, long long int, cuDoubleComplex *, int, long long int, cuDoubleComplex *, int, long long int, cuDoubleComplex *, int, int *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgesvdaStridedBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int rank, int m, int n, const cuDoubleComplex *d_A, int lda, long long int strideA, double *d_S, long long int strideS, cuDoubleComplex *d_U, int ldu, long long int strideU, cuDoubleComplex *d_V, int ldv, long long int strideV, cuDoubleComplex *d_work, int lwork, int *d_info, double *h_R_nrmF, int batchSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgesvdaStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgesvdaStridedBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, const cuDoubleComplex *, int, long long int, double *, long long int, cuDoubleComplex *, int, long long int, cuDoubleComplex *, int, long long int, cuDoubleComplex *, int, int *, double *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgesvdaStridedBatched");
			fprintf(stderr, "wrapper_cusolverDnZgesvdaStridedBatched:%p\n", wrapper_cusolverDnZgesvdaStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgesvdaStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgesvdaStridedBatched(handle, jobz, rank, m, n, d_A, lda, strideA, d_S, strideS, d_U, ldu, strideU, d_V, ldv, strideV, d_work, lwork, d_info, h_R_nrmF, batchSize);
		return retval;
	}
}