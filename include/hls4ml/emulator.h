#ifndef HLS4ML_EMULATOR_H_
#define HLS4ML_EMULATOR_H_

#include <iostream>
#include <string>
#include <any>
#include <dlfcn.h>
#include <memory>

namespace hls4mlEmulator
{
    class Model {
    public:
        virtual void predict(std::any input, std::any result) const = 0;
        virtual ~Model() = default;
    };

    typedef Model* create_model_cls();
    typedef void destroy_model_cls(Model*);

    class ModelLoader {
    private:
        std::string model_name_;
        void* model_lib_;

    public:
        ModelLoader(std::string model_name);
        ModelLoader(ModelLoader const&) = delete;
        ModelLoader& operator=(ModelLoader const&) = delete;
        //prevent move constructor/assignment
        ModelLoader(ModelLoader&&) = delete;
        ModelLoader& operator=(ModelLoader&&) = delete;

        ~ModelLoader();

        std::shared_ptr<Model> load_model();
    };
}

#endif

