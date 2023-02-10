#ifndef HLS4ML_EMULATOR_H_
#define HLS4ML_EMULATOR_H_

#include <iostream>
#include <string>
#include <any>
#include <dlfcn.h>

namespace hls4mlEmulator
{
    class Model {
    public:
        virtual void prepare_input(std::any input) = 0;
        virtual void predict() = 0;
        virtual void read_result(std::any result) = 0;
        virtual ~Model() = default;
    };

    typedef Model* create_model_cls();
    typedef void destroy_model_cls(Model*);

    class ModelLoader {
    private:
        std::string model_name_;
        void* model_lib_;
        Model* model_ = nullptr;

    public:
        ModelLoader(std::string model_name);
        //prevent copying
        ModelLoader(ModelLoader const&) = delete;
        ModelLoader& operator=(ModelLoader const&) = delete;
        //prevent move constructor/assignment
        ModelLoader(ModelLoader&&) = delete;
        ModelLoader& operator=(ModelLoader&&) = delete;
        
        ~ModelLoader();

        Model* load_model();
        void destroy_model();
    };
}

#endif

