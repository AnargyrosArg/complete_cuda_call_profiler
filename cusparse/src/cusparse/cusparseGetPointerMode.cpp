#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseGetPointerMode)(cusparseHandle_t, cusparsePointerMode_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseGetPointerMode(cusparseHandle_t handle, cusparsePointerMode_t *mode) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetPointerMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetPointerMode = (cusparseStatus_t (*)(cusparseHandle_t, cusparsePointerMode_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetPointerMode");
			fprintf(stderr, "wrapper_cusparseGetPointerMode:%p\n", wrapper_cusparseGetPointerMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetPointerMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseGetPointerMode(handle, mode);
		return retval;
	}
}