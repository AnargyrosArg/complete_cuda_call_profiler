#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgetrfBatched)(cublasHandle_t, int, double * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgetrfBatched(cublasHandle_t handle, int n, double * const A[], int lda, int *P, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgetrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgetrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, double * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgetrfBatched");
			fprintf(stderr, "wrapper_cublasDgetrfBatched:%p\n", wrapper_cublasDgetrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgetrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgetrfBatched(handle, n, A, lda, P, info, batchSize);
		return retval;
	}
}