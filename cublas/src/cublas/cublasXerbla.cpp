#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cublasXerbla)(const char *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	void cublasXerbla(const char *srName, int info) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasXerbla)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasXerbla = (void (*)(const char *, int)) dlsym(libwrapper_handle, "wrapper_cublasXerbla");
			fprintf(stderr, "wrapper_cublasXerbla:%p\n", wrapper_cublasXerbla);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasXerbla():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cublasXerbla(srName, info);
	}
}