#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseLoggerSetMask)(int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseLoggerSetMask(int mask) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseLoggerSetMask)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseLoggerSetMask = (cusparseStatus_t (*)(int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerSetMask");
			fprintf(stderr, "wrapper_cusparseLoggerSetMask:%p\n", wrapper_cusparseLoggerSetMask);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseLoggerSetMask():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseLoggerSetMask(mask);
		return retval;
	}
}