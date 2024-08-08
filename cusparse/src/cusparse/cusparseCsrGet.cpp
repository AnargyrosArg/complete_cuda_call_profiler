#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCsrGet)(cusparseSpMatDescr_t, int64_t *, int64_t *, int64_t *, void **, void **, void **, cusparseIndexType_t *, cusparseIndexType_t *, cusparseIndexBase_t *, cudaDataType *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCsrGet(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *nnz, void **csrRowOffsets, void **csrColInd, void **csrValues, cusparseIndexType_t *csrRowOffsetsType, cusparseIndexType_t *csrColIndType, cusparseIndexBase_t *idxBase, cudaDataType *valueType) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCsrGet)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCsrGet = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int64_t *, int64_t *, int64_t *, void **, void **, void **, cusparseIndexType_t *, cusparseIndexType_t *, cusparseIndexBase_t *, cudaDataType *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCsrGet");
			fprintf(stderr, "wrapper_cusparseCsrGet:%p\n", wrapper_cusparseCsrGet);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCsrGet():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCsrGet(spMatDescr, rows, cols, nnz, csrRowOffsets, csrColInd, csrValues, csrRowOffsetsType, csrColIndType, idxBase, valueType);
		return retval;
	}
}