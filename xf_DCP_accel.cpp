#include "xf_channel_extract_config.h"

extern "C" {
void channel_extract_accel(
    ap_uint<INPUT_PTR_WIDTH>* img_rgba1,ap_uint<INPUT_PTR_WIDTH>* img_rgba2,ap_uint<INPUT_PTR_WIDTH>* img_rgba3, ap_uint<OUTPUT_PTR_WIDTH>* img_gray, unsigned char* process_shape, uint16_t channel1,uint16_t channel2,uint16_t channel3, int rows, int cols) {
// clang-format off
    #pragma HLS INTERFACE m_axi     port=img_rgba1  	offset=slave bundle=gmem1
    #pragma HLS INTERFACE m_axi     port=img_rgba2 	offset=slave bundle=gmem2
    #pragma HLS INTERFACE m_axi     port=img_rgba3 	offset=slave bundle=gmem3
    #pragma HLS INTERFACE m_axi     port=img_gray  	offset=slave bundle=gmem4
    #pragma HLS INTERFACE m_axi      port=process_shape offset=slave  bundle=gmem4
    #pragma HLS INTERFACE s_axilite port=rows              	 bundle=control
    #pragma HLS INTERFACE s_axilite port=cols              	 bundle=control
    #pragma HLS INTERFACE s_axilite port=channel1              	 bundle=control
    #pragma HLS INTERFACE s_axilite port=channel2              	 bundle=control
    #pragma HLS INTERFACE s_axilite port=channel3              	 bundle=control
    #pragma HLS INTERFACE s_axilite port=return              bundle=control
    // clang-format on

    xf::cv::Mat<XF_8UC4, HEIGHT, WIDTH, XF_NPPC1> imgInput0;
// clang-format off
    #pragma HLS stream variable=imgInput0.data depth=2
    // clang-format on
    imgInput0.rows = rows;
    imgInput0.cols = cols;
 xf::cv::Mat<XF_8UC4, HEIGHT, WIDTH, XF_NPPC1> imgInput1;
// clang-format off
    #pragma HLS stream variable=imgInput1.data depth=2
    // clang-format on
    imgInput1.rows = rows;
    imgInput1.cols = cols;

////////////////////////////////////
 xf::cv::Mat<XF_8UC4, HEIGHT, WIDTH, XF_NPPC1> imgInput2;
// clang-format off
    #pragma HLS stream variable=imgInput2.data depth=2
    // clang-format on
    imgInput2.rows = rows;
    imgInput2.cols = cols;

////////////////////////////////////

    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput0;
// clang-format off
    #pragma HLS stream variable=imgOutput0.data depth=2
    // clang-format on
    imgOutput0.rows = rows;

    imgOutput0.cols = cols;

  xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput1;
// clang-format off
  #pragma HLS stream variable=imgOutput1.data depth=2
    // clang-format on
    imgOutput1.rows = rows;
    imgOutput1.cols = cols;

  xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput2;
// clang-format off
  #pragma HLS stream variable=imgOutput2.data depth=2
    // clang-format on
    imgOutput2.rows = rows;
    imgOutput2.cols = cols;


  xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput3;
// clang-format off
  #pragma HLS stream variable=imgOutput3.data depth=2
    // clang-format on
    imgOutput3.rows = rows;
    imgOutput3.cols = cols;

  xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput4;
// clang-format off
  #pragma HLS stream variable=imgOutput4.data depth=2
    // clang-format on
    imgOutput4.rows = rows;
    imgOutput4.cols = cols;


  xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput5;
// clang-format off
  #pragma HLS stream variable=imgOutput5.data depth=2
    // clang-format on
    imgOutput5.rows = rows;
    imgOutput5.cols = cols;


  xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput6;
// clang-format off
  #pragma HLS stream variable=imgOutput6.data depth=2
    // clang-format on
    imgOutput6.rows = rows;
    imgOutput6.cols = cols;
//////////////////////////////////////////////////////////

  unsigned char _kernel[FILTER_SIZE * FILTER_SIZE];
    for (unsigned int i = 0; i < FILTER_SIZE * FILTER_SIZE; ++i) {
// clang-format off
        #pragma HLS PIPELINE
        // clang-format on
        _kernel[i] = process_shape[i];
    }
//////////////////////////////////////////////////////////

// clang-format off
  #pragma HLS DATAFLOW
    // clang-format on
    xf::cv::Array2xfMat<INPUT_PTR_WIDTH, XF_8UC4, HEIGHT, WIDTH, XF_NPPC1>(img_rgba1, imgInput0);
    xf::cv::Array2xfMat<INPUT_PTR_WIDTH, XF_8UC4, HEIGHT, WIDTH, XF_NPPC1>(img_rgba2, imgInput1);
    xf::cv::Array2xfMat<INPUT_PTR_WIDTH, XF_8UC4, HEIGHT, WIDTH, XF_NPPC1>(img_rgba3, imgInput2);
    xf::cv::extractChannel<XF_8UC4, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(imgInput0, imgOutput0, channel1);
    xf::cv::extractChannel<XF_8UC4, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(imgInput1, imgOutput1, channel2);
    xf::cv::extractChannel<XF_8UC4, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(imgInput2, imgOutput2, channel3);
    xf::cv::min<XF_8UC1,HEIGHT, WIDTH, XF_NPPC1>(imgOutput0, imgOutput1, imgOutput3);
    xf::cv::min<XF_8UC1,HEIGHT, WIDTH, XF_NPPC1>(imgOutput2, imgOutput3, imgOutput4);
    xf::cv::erode<XF_BORDER_CONSTANT, XF_8UC1, HEIGHT, WIDTH, XF_KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ITERATIONS, XF_NPPC1>(imgOutput4, imgOutput5,_kernel);
    xf::cv::medianBlur<FILTER_SIZE, XF_BORDER_REPLICATE, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(imgOutput5, imgOutput6);
    xf::cv::xfMat2Array<OUTPUT_PTR_WIDTH, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(imgOutput6, img_gray);  
}
}
