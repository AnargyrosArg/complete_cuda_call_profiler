#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtLoggerSetFile)(FILE *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtLoggerSetFile(FILE *file){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtLoggerSetFile)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtLoggerSetFile = (cublasStatus_t (*)(FILE *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtLoggerSetFile");
			fprintf(stderr, "wrapper_cublasLtLoggerSetFile:%p\n", wrapper_cublasLtLoggerSetFile);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtLoggerSetFile():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtLoggerSetFile(file);
		return retval;
	}
}