#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyBsrsm2Info)(bsrsm2Info_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyBsrsm2Info(bsrsm2Info_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyBsrsm2Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyBsrsm2Info = (cusparseStatus_t (*)(bsrsm2Info_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyBsrsm2Info");
			fprintf(stderr, "wrapper_cusparseDestroyBsrsm2Info:%p\n", wrapper_cusparseDestroyBsrsm2Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyBsrsm2Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyBsrsm2Info(info);
		return retval;
	}
}