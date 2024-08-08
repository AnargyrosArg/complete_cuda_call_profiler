#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseLoggerSetFile)(FILE *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseLoggerSetFile(FILE *file) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseLoggerSetFile)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseLoggerSetFile = (cusparseStatus_t (*)(FILE *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerSetFile");
			fprintf(stderr, "wrapper_cusparseLoggerSetFile:%p\n", wrapper_cusparseLoggerSetFile);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseLoggerSetFile():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseLoggerSetFile(file);
		return retval;
	}
}