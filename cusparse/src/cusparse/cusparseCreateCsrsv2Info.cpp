#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateCsrsv2Info)(csrsv2Info_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateCsrsv2Info(csrsv2Info_t *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateCsrsv2Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateCsrsv2Info = (cusparseStatus_t (*)(csrsv2Info_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateCsrsv2Info");
			fprintf(stderr, "wrapper_cusparseCreateCsrsv2Info:%p\n", wrapper_cusparseCreateCsrsv2Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateCsrsv2Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateCsrsv2Info(info);
		return retval;
	}
}