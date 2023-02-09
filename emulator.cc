#include "emulator.h"

using namespace hls4mlEmulator;

ModelLoader::ModelLoader(std::string model_name)
{
    model_name_ = std::move(model_name);
    model_name_.append(".so");
}

ModelLoader::~ModelLoader(){
    dlclose(model_lib_);
}

Model* ModelLoader::load_model()
{
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

void ModelLoader::destroy_model()
{
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