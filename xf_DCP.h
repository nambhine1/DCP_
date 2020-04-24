#ifndef _XF_CHANNEL_EXTRACT_CONFIG_H_
#define _XF_CHANNEL_EXTRACT_CONFIG_H_
#include "imgproc/xf_median_blur.hpp"
#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.hpp"
#include "common/xf_utility.hpp"
#include "imgproc/xf_channel_extract.hpp"
#include "core/xf_arithm.hpp"
#include "imgproc/xf_erosion.hpp"
#include "imgproc/xf_hist_equalize.hpp"
#include "xf_config_params.h"


// Image width and height
#define HEIGHT 2160
#define WIDTH 3840


#define FILTER_SIZE 3
#define KERNEL_SHAPE 0 // 0 - rectangle, 1 - ellipse, 2 - cross
#define ITERATIONS 1

#if NO
#define OUT_TYPE ap_uint<8> // ap_uinnt8_t
#define IN_TYPE ap_uint<32> // ap_uint32_t
//#define INPUT_CH_TYPE XF_RGBA
//#define INPUT_CH_TYPE XF_GRAY
#elif RO
#define OUT_TYPE ap_uint<64> // ap_uint64_t
#define IN_TYPE ap_uint<64>  // ap_uint256_t
#endif

#if KERNEL_SHAPE == 0
#define XF_KERNEL_SHAPE XF_SHAPE_RECT
#elif KERNEL_SHAPE == 1
#define XF_KERNEL_SHAPE XF_SHAPE_ELLIPSE
#elif KERNEL_SHAPE == 2
#define XF_KERNEL_SHAPE XF_SHAPE_CROSS
#else
#define XF_KERNEL_SHAPE XF_SHAPE_RECT
#endif

#endif //_XF_CHANNEL_EXTRACT_CONFIG_H_
