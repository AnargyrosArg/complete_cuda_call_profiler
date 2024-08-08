#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgetriBatched)(cublasHandle_t, int, const float * const*, int, const int *, float * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgetriBatched(cublasHandle_t handle, int n, const float * const A[], int lda, const int *P, float * const C[], int ldc, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgetriBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgetriBatched = (cublasStatus_t (*)(cublasHandle_t, int, const float * const*, int, const int *, float * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasSgetriBatched");
			fprintf(stderr, "wrapper_cublasSgetriBatched:%p\n", wrapper_cublasSgetriBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgetriBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
		return retval;
	}
}