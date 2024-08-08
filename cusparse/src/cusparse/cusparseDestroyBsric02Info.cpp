#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyBsric02Info)(bsric02Info_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyBsric02Info(bsric02Info_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyBsric02Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyBsric02Info = (cusparseStatus_t (*)(bsric02Info_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyBsric02Info");
			fprintf(stderr, "wrapper_cusparseDestroyBsric02Info:%p\n", wrapper_cusparseDestroyBsric02Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyBsric02Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyBsric02Info(info);
		return retval;
	}
}