#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnGesvd)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, size_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnGesvd(cusolverDnHandle_t handle, cusolverDnParams_t params, signed char jobu, signed char jobvt, int64_t m, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, cudaDataType dataTypeS, void *S, cudaDataType dataTypeU, void *U, int64_t ldu, cudaDataType dataTypeVT, void *VT, int64_t ldvt, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnGesvd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnGesvd = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, size_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnGesvd");
			fprintf(stderr, "wrapper_cusolverDnGesvd:%p\n", wrapper_cusolverDnGesvd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnGesvd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnGesvd(handle, params, jobu, jobvt, m, n, dataTypeA, A, lda, dataTypeS, S, dataTypeU, U, ldu, dataTypeVT, VT, ldvt, computeType, pBuffer, workspaceInBytes, info);
		return retval;
	}
}