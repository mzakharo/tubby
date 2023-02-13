FLAGS= -DTF_LITE_STATIC_MEMORY
all:
	g++ micro.cc $(FLAGS) -I tflite-micro -I tflite-micro/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include -I tflite-micro/tensorflow/lite/micro/tools/make/downloads/gemmlowp/ -ltensorflow-microlite -L tflite-micro/gen/linux_x86_64_default/lib/

tflite:
	cd tflite-micro && make -f tensorflow/lite/micro/tools/make/Makefile -j4

gen:
	xxd -i model_fc.tflite > micropython/tfmicro/model_fc.h
	
