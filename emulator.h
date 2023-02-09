#ifndef HLS4ML_EMULATOR_H_
#define HLS4ML_EMULATOR_H_

#include <iostream>
#include <string>
#include <any>
#include <dlfcn.h>

class HLS4MLModel {
public:
    virtual void prepare_input(std::any input) = 0;
    virtual void predict() = 0;
    virtual void read_result(std::any result) = 0;
    virtual ~HLS4MLModel() = default;
};

typedef HLS4MLModel* create_model_cls();
typedef void destroy_model_cls(HLS4MLModel*);

class ModelLoader {
private:
    std::string model_name_;
    void* model_lib_;
    HLS4MLModel* model_ = nullptr;

public:
    ModelLoader(std::string model_name) {
        model_name_ = model_name;
        model_name_.append(".so");
    }
    
    ~ModelLoader() {
        dlclose(model_lib_);
    }

    HLS4MLModel* load_model() {
        model_lib_ = dlopen(model_name_.c_str(), RTLD_LAZY | RTLD_LOCAL);
        if (!model_lib_) {
            std::cerr << "Cannot load library: " << dlerror() << std::endl;
            throw "hls4ml emulator load_model() failure!";
        }
        
        create_model_cls* create_model = (create_model_cls*) dlsym(model_lib_, "create_model");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol 'create_model': " << dlsym_error << std::endl;
            throw "hls4ml emulator create_model() failure!";
        }
        
        model_ = create_model();
        
        return model_;
    }
    
    void destroy_model() {
        destroy_model_cls* destroy = (destroy_model_cls*) dlsym(model_lib_, "destroy_model");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol destroy_model: " << dlsym_error << std::endl;
            throw "hls4ml emulator destroy_model() failure!";
        }
        if (model_ != nullptr) {
            destroy(model_);
        }
    }

};

#endif

