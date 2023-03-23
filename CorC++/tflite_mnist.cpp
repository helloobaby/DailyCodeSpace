extern "C"{
    #define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
}
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_optional_debug_tools.h"
extern "C" {
#include "tjpgd.h"
}
typedef unsigned int UINT;
typedef unsigned char BYTE;
UINT in_func (JDEC* jd, BYTE* buff, UINT nbyte);
int out_func (JDEC* jd, void* bitmap, JRECT* rect);
typedef struct {
    FILE* fp;
    BYTE *fbuf;
    UINT wfbuf;
} IODEV;
struct RGB{
    unsigned char r,g,b;
};
class RTT_ERROR_REPORT:public tflite::ErrorReporter{
public:
    virtual int Report(const char* format, va_list args){
        char buffer[256];
        buffer[255]='\n';
        vsnprintf(buffer,256,format,args);
        printf(buffer);
        return 0;
    }
};
extern "C" int main()
{
    // 读取模型
  FILE* fd = fopen("/sdcard/mnist.tflite", "rb");
    if(fd == 0){
        perror("???");
        printf("文件打开失败\n");
        return 0;
    }
    char* fbuf = (char*)malloc(377200);
    if(!fbuf){
        printf("内存分配失败\n");
        return 0;
    }
    fread(fbuf,1,377200,fd);


    // 加载模型
    const tflite::Model* model = tflite::GetModel(fbuf);
    printf("模型版本 : %d\n", model->version());

    tflite::MicroMutableOpResolver<6> resolver;
    resolver.AddConv2D();
    resolver.AddMaxPool2D();
    resolver.AddReshape();
    resolver.AddFullyConnected();
    resolver.AddSoftmax();
    //TFLITE_SCHEMA_VERSION
    /*
    12 bytes lost due to alignment.
    To avoid this loss, please make sure the tensor_arena is 16 bytes aligned.
    Arena size is too small for activation buffers.
    Needed 108160 but only 8992 was available
         下面这个大小要不断增大,直到不报错
    108160=1024*105
         不能超出可用RAM大小
     */
    constexpr int kTensorArenaSize = 205*1024;
    // https://github.com/espressif/tflite-micro-esp-examples/issues/3
    // 用rt_malloc/栈空间不够
    uint8_t* tensor_arena = (uint8_t*)malloc(kTensorArenaSize);
    if(!tensor_arena){
        printf("内存不够\n");
        return 0;
    }
    RTT_ERROR_REPORT error_reporter;
    tflite::MicroInterpreter interpreter(model, resolver,
                   tensor_arena,kTensorArenaSize,&error_reporter);

    if(interpreter.initialization_status() != kTfLiteOk){
        printf("解释器初始化失败\n");
        return 0;
    }

    TfLiteStatus allocate_status;
    allocate_status = interpreter.AllocateTensors();
    if(allocate_status != kTfLiteOk){
        printf("AllocateTensors 失败\n");
        return 0;
    }
    interpreter.input_tensor(0);
    interpreter.typed_input_tensor<float>(0);

    void* work = malloc(50000);
    JDEC jdec;
    IODEV devid;
    devid.fp = fopen("/sdcard/0.jpg", "rb");
    if(!devid.fp){
        printf("图像打开失败\n");
        return 0;
    }
    typedef size_t (*fcp)(JDEC *, uint8_t *, size_t);
    JRESULT res = jd_prepare(&jdec, (fcp)in_func, work, 50000, &devid);
    if(res != JDR_OK){
      printf("%d\n",res);
        printf("jpg 图像解码失败\n");
        return 0;
    }
    printf("Image dimensions: %u by %u. %u bytes used.\n",
            jdec.width, jdec.height, (unsigned int)(50000 - jdec.sz_pool));
    devid.fbuf = (BYTE*)malloc(3 * jdec.width * jdec.height);
    devid.wfbuf = jdec.width;
    res = jd_decomp(&jdec, out_func, 0);
    if (res == JDR_OK) {
        printf("ok\n");
    }else{
        printf("not ok\n");
    }

    //


    // 训练的图片是28*28的灰度的,需要将rgb888的图片转成灰度
    TfLiteTensor* input_data_ptr = interpreter.input(0);
    float* gray = (float*)malloc(4*28*28);
    RGB* rgb = (RGB*)devid.fbuf;
    for(int i = 0;i<28;i++){
        for(int j = 0;j<28;j++){
            //printf("%u %u %u\n",rgb->r,rgb->g,rgb->b);
            *(gray+i*28+j) = rgb[i*28+j].r;
        }
    }


    for(int i = 0;i<28;i++){
        printf("input[%d][]\n",i);
        for(int j = 0;j<28;j++){
            // 输出灰度后的像素值
            //printf("%f ",*(gray+j*28+i));
            // 归一化
            float d = 1.0-(float)(*(gray+i*28+j))/255.f;
            input_data_ptr->data.f[i*28+j] = d;
            printf("%f ",d);
            //input_data_ptr++;
        }
        printf("\n");
    }

    tflite::PrintInterpreterState(&interpreter);
    // 运行模型
    interpreter.Invoke();
    printf("Invoke Done.\n");

    TfLiteTensor* output = nullptr;
    output = interpreter.output(0);
    for (int i = 0; i < 10; i++)
    {
        //https://club.rt-thread.org/ask/question/04dc44403aedf571.html
        // printf正常打印浮点
        printf("Result %d: %f\n", i, output->data.f[i]);
    }

    return 0;
}

unsigned int in_func (JDEC* jd, uint8_t* buff, unsigned int nbyte)
{
    IODEV *dev = (IODEV*)jd->device;
    if (buff) {
        /* Read bytes from input stream */
        return (uint16_t)fread(buff, 1, nbyte, dev->fp);
    } else {
        /* Remove bytes from input stream */
        return fseek(dev->fp, nbyte, SEEK_CUR) ? 0 : nbyte;
    }
}
int out_func (JDEC* jd, void* bitmap, JRECT* rect)
{
    IODEV *dev = (IODEV*)jd->device;
    BYTE *src, *dst;
    UINT y, bws, bwd;

    if (rect->left == 0) {
        //printf("\r%lu%%", (rect->top << jd->scale) * 100UL / jd->height);
    }

    src = (BYTE*)bitmap;

    dst = dev->fbuf + 3 * (rect->top * dev->wfbuf + rect->left);
    bws = 3 * (rect->right - rect->left + 1);
    bwd = 3 * dev->wfbuf;
    for (y = rect->top; y <= rect->bottom; y++) {
        memcpy(dst, src, bws);
        src += bws; dst += bwd;
    }

    //RGB* src2 = (RGB*)dst;
    //for(int i= 0;i<28;i++){
        //printf("(%d %d %d)\n",(src2+i)->r,(src2+i)->g,(src2+i)->b);
    //}

    return 1;
}

