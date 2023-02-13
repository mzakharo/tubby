CPPEXAMPLE_MOD_DIR := $(USERMOD_DIR)

# Add our source files to the respective variables.
SRC_USERMOD += $(CPPEXAMPLE_MOD_DIR)/tfmicromodule.c
SRC_USERMOD_CXX += $(CPPEXAMPLE_MOD_DIR)/tfmicro.cpp

# Add our module directory to the include path.
CFLAGS_USERMOD += -I$(CPPEXAMPLE_MOD_DIR)
CXXFLAGS_USERMOD += -I$(CPPEXAMPLE_MOD_DIR) -std=c++11 -DTF_LITE_STATIC_MEMORY -I$(CPPEXAMPLE_MOD_DIR)/../../tflite-micro -I$(CPPEXAMPLE_MOD_DIR)/../../tflite-micro/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include -I$(CPPEXAMPLE_MOD_DIR)/../../tflite-micro/tensorflow/lite/micro/tools/make/downloads/gemmlowp/ # We use C++ features so have to link against the standard library.
LDFLAGS_USERMOD += -lstdc++  -ltensorflow-microlite -L $(CPPEXAMPLE_MOD_DIR)/../../tflite-micro/gen/linux_x86_64_default/lib/

