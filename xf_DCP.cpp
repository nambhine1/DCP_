
#include "dcp_core.h"
using namespace cv::ximgproc;
#include "common/xf_headers.hpp"
#include "xf_channel_extract_config.h"

#include "xcl2.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid Number of Arguments!\nUsage:\n");
        fprintf(stderr, "<Executable Name> <Input image>\n");
        return -1;
    }

    cv::Mat in_src, in_rgba, out_img;
    // read image
    in_src = cv::imread(argv[1], 1);

    if (in_src.data == NULL) {
        fprintf(stderr, "Cannot open image \n");
        return 0;
    }

    out_img.create(in_src.rows, in_src.cols, CV_8U);
    cv::cvtColor(in_src, in_rgba, CV_BGR2RGBA);
    uint16_t channel1 = XF_EXTRACT_CH_R;
    uint16_t channel2 = XF_EXTRACT_CH_G;
    uint16_t channel3 = XF_EXTRACT_CH_G;
   
    cv::Mat element = cv::getStructuringElement(0, cv::Size(FILTER_SIZE, FILTER_SIZE), cv::Point(-1, -1));

    /////////////////////////////////////// CL ////////////////////////
    int height = in_rgba.rows;
    int width = in_rgba.cols;
 
    std::vector<unsigned char, aligned_allocator<unsigned char> > shape(FILTER_SIZE * FILTER_SIZE);

    for (int i = 0; i < (FILTER_SIZE * FILTER_SIZE); i++) {
        shape[i] = element.data[i];
    }



    size_t vec_in_size_bytes = FILTER_SIZE * FILTER_SIZE * sizeof(unsigned char);
    std::vector<cl::Device> devices = xcl::get_xil_devices();
    cl::Device device = devices[0];
    cl::Context context(device);

    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);

    std::string device_name = device.getInfo<CL_DEVICE_NAME>();
    std::string binaryFile = xcl::find_binary_file(device_name, "krnl_channelextract");
    cl::Program::Binaries bins = xcl::import_binary_file(binaryFile);
    devices.resize(1);
    cl::Program program(context, devices, bins);
    cl::Kernel krnl(program, "channel_extract_accel");

    std::vector<cl::Memory> inBuf_rgba, outBuf_gray;
    cl::Buffer imageToDevicergba(context, CL_MEM_READ_ONLY, (in_rgba.rows * in_rgba.cols * 4));
    cl::Buffer buffer_inShape(context, CL_MEM_READ_ONLY, vec_in_size_bytes, NULL);
    cl::Buffer imageFromDevicegray(context, CL_MEM_WRITE_ONLY, (in_rgba.rows * in_rgba.cols * 1));
   


    printf("finished buffer creation task\n");

    inBuf_rgba.push_back(imageToDevicergba);
    outBuf_gray.push_back(imageFromDevicegray);

    /* Copy input vectors to memory */
    q.enqueueWriteBuffer(imageToDevicergba, CL_TRUE, 0, (in_rgba.rows * in_rgba.cols * 4), in_rgba.data); /* 0 means from host*/
    printf("finished enqueueing task\n");

    // Set the kernel arguments
    krnl.setArg(0, imageToDevicergba);
    krnl.setArg(1, imageToDevicergba);
    krnl.setArg(2, imageToDevicergba);
    krnl.setArg(3, imageFromDevicegray);
    krnl.setArg(4, buffer_inShape);
    krnl.setArg(5, channel1);
    krnl.setArg(6, channel2);
    krnl.setArg(7, channel3);
    krnl.setArg(8, height);
    krnl.setArg(9, width);

    printf("finished setting kernel arguments\n");

    // Profiling Objects
    cl_ulong start = 0;
    cl_ulong end = 0;
    double diff_prof = 0.0f;
    cl::Event event_sp;
    printf("started kernel execution\n");
    // Launch the kernel
    q.enqueueTask(krnl, NULL, &event_sp);
    clWaitForEvents(1, (const cl_event*)&event_sp);

    printf("finished kernel execution\n");
    event_sp.getProfilingInfo(CL_PROFILING_COMMAND_START, &start);
    event_sp.getProfilingInfo(CL_PROFILING_COMMAND_END, &end);
    diff_prof = end - start;
    std::cout << (diff_prof / 1000000) << "ms" << std::endl;

    q.enqueueReadBuffer(imageFromDevicegray, CL_TRUE, 0, (in_rgba.rows * in_rgba.cols), out_img.data);
    q.finish();
    printf("write output buffer\n");
    /////////////////////////////////////// end of CL /////////////////////
	CalcRecover(recover, in_src, out_img, Airlight);	
    cv::imwrite("hls_out.png", recover);

    std::vector<cv::Mat> bgr_planes;
    // call OpenCV function
    cv::split(in_src, bgr_planes);
    // write output and OpenCV reference image
    cv::imwrite("out_ocv.png", bgr_planes[2]);

    cv::Mat diff;
    diff.create(in_src.rows, in_src.cols, CV_8U);

    // Check with the correct channel. Keep 2 for R, 1 for G and 0 for B in index of bgr_planes
    cv::absdiff(bgr_planes[2], out_img, diff);
    cv::imwrite("diff.jpg", diff);

    // Find minimum and maximum differences.
    double minval = 256, maxval = 0;
    int cnt = 0;
    for (int i = 0; i < diff.rows; i++) {
        for (int j = 0; j < diff.cols; j++) {
            unsigned char v = diff.at<unsigned char>(i, j);
            if (v > 0) cnt++;
            if (minval > v) minval = v;
            if (maxval < v) maxval = v;
        }
    }

    float err_per = 100.0 * (float)cnt / (in_src.rows * in_src.cols);

    fprintf(stderr,
            "Minimum error in intensity = %f\n"
            "Maximum error in intensity = %f\n"
            "Percentage of pixels above error threshold = %f\n",
            minval, maxval, err_per);

    if (err_per > 0.0f) return -1;

    return 0;
}
