#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyBsrilu02Info)(bsrilu02Info_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyBsrilu02Info(bsrilu02Info_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyBsrilu02Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyBsrilu02Info = (cusparseStatus_t (*)(bsrilu02Info_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyBsrilu02Info");
			fprintf(stderr, "wrapper_cusparseDestroyBsrilu02Info:%p\n", wrapper_cusparseDestroyBsrilu02Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyBsrilu02Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyBsrilu02Info(info);
		return retval;
	}
}