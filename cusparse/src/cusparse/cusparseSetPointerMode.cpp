#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetPointerMode)(cusparseHandle_t, cusparsePointerMode_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetPointerMode(cusparseHandle_t handle, cusparsePointerMode_t mode) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetPointerMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetPointerMode = (cusparseStatus_t (*)(cusparseHandle_t, cusparsePointerMode_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetPointerMode");
			fprintf(stderr, "wrapper_cusparseSetPointerMode:%p\n", wrapper_cusparseSetPointerMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetPointerMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetPointerMode(handle, mode);
		return retval;
	}
}