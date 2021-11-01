/*
Copyright 2020 Peter Stoiber

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Please contact the author if you need another license.
This Repository is provided "as is", without warranties of any kind.

*/

#ifndef libuvc_support_h__
#define libuvc_support_h__
#include </home/peter/Android/Sdk/ndk/21.1.6352462/sysroot/usr/include/android/native_window.h>
#include </home/peter/Android/Sdk/ndk/21.1.6352462/sysroot/usr/include/jni.h>
#include <libusb.h>

//////////////// Auto Detect Methods ////////////////////
struct AutotransferStruct; /* Forward declaration */
typedef struct AutotransferStruct {
    int packetCnt;
    int packet0Cnt;
    int packet12Cnt;
    int packetDataCnt;
    int packetHdr8Ccnt;
    int packetErrorCnt;
    int frameCnt;
    int frameLen;
    int requestCnt;
    int sframeLenArray[5];
} AutotransferStruct;

extern AutotransferStruct get_autotransferStruct();

////////////////////// TEST 1 FRAME METHODS //////////////////////////

struct ManualTestFrameStruct; /* Forward declaration */
typedef struct ManualTestFrameStruct {
    int packetCnt;
    int packet0Cnt;
    int packet12Cnt;
    int packetDataCnt;
    int packetHdr8Ccnt;
    int packetErrorCnt;
    int frameCnt;
    int frameLen;
    int requestCnt;
    int sframeLenArray[5];
} ManualTestFrameStruct;

extern ManualTestFrameStruct get_ManualTestFrameStruct();

//////////////// Global Methods ////////////////////

//   Camera Initialization Methods
extern int set_the_native_Values (int FD, int packetsPerReques, int maxPacketSiz, int activeUrb, int camStreamingAltSettin, int camFormatInde,
                 int camFrameInde, int camFrameInterva, int imageWidt, int imageHeigh, int camStreamingEndpointAdress, int camStreamingInterfaceNumber,
                 const char* frameformat, int numberOfAutoFrame, int bcdUVC_int, int lowAndroid);
extern int initStreamingParms(int FD);
extern void stopStreaming();
extern void stopJavaVM();
extern void exit_native();
extern void closeLibUsb();
extern int libUsb_open_def_fd(int vid, int pid, const char *serial, int fd, int busnum, int devaddr);
extern unsigned char * probeCommitControl();



// Camera Set up Methods
extern void startAutoDetection ();
extern void getFramesOverLibUsb(int yuvFrameIsZero, int stream, int whichTestrun);
extern int awaitFrame () ;
extern void probeCommitControl_cleanup();
extern void sendCtlForConnection(int bmHin, int camFormatInde, int camFrameInde, int camFrameInterva);
      // Callback Methods
typedef int ( *autoStreamComplete)();
extern void setAutoStreamComplete(autoStreamComplete autoStream);
typedef int ( *eventCallback)(unsigned char *videoframe, int value);
extern void setCallback(eventCallback evnHnd);
typedef int ( *jnaFrameCallback)(void  *videoframe, int value);
extern void setJnaFrameCallback(jnaFrameCallback evnHnd);
extern int eheckEventHandling();
extern unsigned char * probeCommitControl(int bmHin, int camFormatInde, int camFrameInde, int camFrameInterva, int FD);
typedef int ( *frameComplete)(int bitmap);
extern void setFrameComplete(frameComplete evnHnd);

////////// Activity Strteam
extern int setPreviewDisplay(ANativeWindow *preview_window);
// horizontalFlip == 1) horizontalFlip = true;
extern void setRotation(int rot, int horizontalFl, int verticalFl);
extern int fetchTheCamStreamingEndpointAdress (int FD);
extern void setImageCapture();
extern void setImageCaptureLongClick();
extern void startVideoCapture();
extern void stopVideoCapture();
extern void startVideoCaptureLongClick() ;
extern void stopVideoCaptureLongClick() ;
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_JniIsoStreamActivitySurface
        (JNIEnv *, jobject, jobject, jint, jint);
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_JniIsoStreamActivity
        (JNIEnv *, jobject, jint, jint);
// Streaming Method
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_JniSetSurfaceView
        (JNIEnv *, jobject, jobject);
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_JniSetSurfaceYuv
        (JNIEnv *, jobject, jobject);
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_PictureVideoSave
        (JNIEnv* env, jobject thiz, jobject bitmap);

//////////  Frame Conversation:
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_YUY2pixeltobmp( JNIEnv* env, jobject thiz, jbyteArray data, jobject bitmap, int im_width, int im_height);
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_UYVYpixeltobmp( JNIEnv* env, jobject thiz, jbyteArray data, jobject bitmap, int im_width, int im_height);
extern unsigned char* convertUYVYtoJPEG (unsigned char* UYVY_frame_array, int* jpgLength, int UYVYframeLength, int imageWidth, int imageHeight);
        // get Bitmap
JNIEXPORT void JNICALL Java_humer_UvcCamera_StartIsoStreamActivity_frameToBitmap( JNIEnv* env, jobject thiz, jobject bitmap);

///////////////   Stream Service
JNIEXPORT void JNICALL Java_humer_UvcCamera_LibUsb_StartIsoStreamService_JniServiceOverSurface
        (JNIEnv *, jobject);
JNIEXPORT void JNICALL Java_humer_UvcCamera_LibUsb_StartIsoStreamService_JniServiceOverBitmap
        (JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_humer_UvcCamera_LibUsb_StartIsoStreamService_JniGetAnotherFrame
        (JNIEnv *, jobject);
JNIEXPORT void JNICALL Java_humer_UvcCamera_LibUsb_StartIsoStreamService_JniPrepairForStreamingfromService
        (JNIEnv *, jobject);

////////    SetUpTheDevice
JNIEXPORT void JNICALL Java_humer_UvcCamera_SetUpTheUsbDevice_JniIsoStreamActivity
        (JNIEnv *, jobject, jobject, jint, jint);

////////// WebRTC
extern void prepairTheStream_WebRtc_Service();
extern void lunchTheStream_WebRtc_Service();
JNIEXPORT void JNICALL Java_com_example_androidthings_videortc_UsbCapturer_JniWebRtcJavaMethods
        (JNIEnv *, jobject);

////// YUV Methods


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////   CONSTANTS         /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define align_buffer_64(var, size)                                           \
  uint8_t* var##_mem = (uint8_t*)(malloc((size) + 63));         /* NOLINT */ \
  uint8_t* var = (uint8_t*)(((intptr_t)(var##_mem) + 63) & ~63) /* NOLINT */

#define free_aligned_buffer_64(var) \
  free(var##_mem);                  \
  var = 0

// USB codes:
// Request types (bmRequestType):

#define  RT_STANDARD_INTERFACE_SET = 0x01
#define  RT_CLASS_INTERFACE_SET     0x21
#define  RT_CLASS_INTERFACE_GET     0xA1
// Video interface subclass codes:
#define  SC_VIDEOCONTROL            0x01
#define  SC_VIDEOSTREAMING          0x02
#define CLASS_VIDEO                 0x14
// Standard request codes:
#define  SET_INTERFACE              0x0b
// Video class-specific request codes:
#define  SET_CUR                     0x01
#define  GET_CUR                     0x81
// VideoControl interface control selectors (CS):
#define  VC_REQUEST_ERROR_CODE_CONTROL  0x02
// VideoStreaming interface control selectors (CS):
#define  VS_PROBE_CONTROL              0x01
#define  VS_COMMIT_CONTROL             0x02
#define  VS_STILL_PROBE_CONTROL        0x03
#define  VS_STILL_COMMIT_CONTROL       0x04
#define  VS_STREAM_ERROR_CODE_CONTROL  0x06
#define  VS_STILL_IMAGE_TRIGGER_CONTROL  0x05


/** UVC error types, based on libusb errors
 * @ingroup diag
 */
typedef enum uvc_error {
    /** Success (no error) */
    UVC_SUCCESS = 0,
    /** Input/output error */
    UVC_ERROR_IO = -1,
    /** Invalid parameter */
    UVC_ERROR_INVALID_PARAM = -2,
    /** Access denied */
    UVC_ERROR_ACCESS = -3,
    /** No such device */
    UVC_ERROR_NO_DEVICE = -4,
    /** Entity not found */
    UVC_ERROR_NOT_FOUND = -5,
    /** Resource busy */
    UVC_ERROR_BUSY = -6,
    /** Operation timed out */
    UVC_ERROR_TIMEOUT = -7,
    /** Overflow */
    UVC_ERROR_OVERFLOW = -8,
    /** Pipe error */
    UVC_ERROR_PIPE = -9,
    /** System call interrupted */
    UVC_ERROR_INTERRUPTED = -10,
    /** Insufficient memory */
    UVC_ERROR_NO_MEM = -11,
    /** Operation not supported */
    UVC_ERROR_NOT_SUPPORTED = -12,
    /** Device is not UVC-compliant */
    UVC_ERROR_INVALID_DEVICE = -50,
    /** Mode not supported */
    UVC_ERROR_INVALID_MODE = -51,
    /** Resource has a callback (can't use polling and async) */
    UVC_ERROR_CALLBACK_EXISTS = -52,
    /** Undefined error */
    UVC_ERROR_OTHER = -99
} uvc_error_t;

/** Color coding of stream, transport-independent
 * @ingroup streaming
 */
enum uvc_frame_format {
    UVC_FRAME_FORMAT_UNKNOWN = 0,
    /** Any supported format */
    UVC_FRAME_FORMAT_ANY = 0,
    UVC_FRAME_FORMAT_UNCOMPRESSED,
    UVC_FRAME_FORMAT_COMPRESSED,
    /** YUYV/YUV2/YUV422: YUV encoding with one luminance value per pixel and
     * one UV (chrominance) pair for every two pixels.
     */
    UVC_FRAME_FORMAT_YUYV,
    UVC_FRAME_FORMAT_UYVY,
    /** 16-bits RGB */
    UVC_FRAME_FORMAT_RGB565,	// RGB565
    /** 24-bit RGB */
    UVC_FRAME_FORMAT_RGB,		// RGB888
    UVC_FRAME_FORMAT_BGR,		// BGR888
    /* 32-bits RGB */
    UVC_FRAME_FORMAT_RGBX,		// RGBX8888
    /** Motion-JPEG (or JPEG) encoded images */
    UVC_FRAME_FORMAT_MJPEG,
    UVC_FRAME_FORMAT_GRAY8,
    UVC_FRAME_FORMAT_BY8,
    /** Number of formats understood */
    UVC_FRAME_FORMAT_COUNT,
    // YVU420SemiPlanar
    UVC_FRAME_FORMAT__NV21 = 5,
};

#define PIXEL_RGB565		2
#define PIXEL_UYVY			2
#define PIXEL_YUYV			2
#define PIXEL_RGB			3
#define PIXEL_BGR			3
#define PIXEL_RGBX			4

#define PIXEL8_YUYV			PIXEL_YUYV * 8
#define PIXEL8_RGBX			PIXEL_RGBX * 8


#define PIXEL2_RGB565		PIXEL_RGB565 * 2
#define PIXEL2_UYVY			PIXEL_UYVY * 2
#define PIXEL2_YUYV			PIXEL_YUYV * 2
#define PIXEL2_RGB			PIXEL_RGB * 2
#define PIXEL2_BGR			PIXEL_BGR * 2
#define PIXEL2_RGBX			PIXEL_RGBX * 2

#define PIXEL4_RGB565		PIXEL_RGB565 * 4
#define PIXEL4_UYVY			PIXEL_UYVY * 4
#define PIXEL4_YUYV			PIXEL_YUYV * 4
#define PIXEL4_RGB			PIXEL_RGB * 4
#define PIXEL4_BGR			PIXEL_BGR * 4
#define PIXEL4_RGBX			PIXEL_RGBX * 4

#define PIXEL8_RGB565		PIXEL_RGB565 * 8
#define PIXEL8_UYVY			PIXEL_UYVY * 8
#define PIXEL8_YUYV			PIXEL_YUYV * 8
#define PIXEL8_RGB			PIXEL_RGB * 8
#define PIXEL8_BGR			PIXEL_BGR * 8
#define PIXEL8_RGBX			PIXEL_RGBX * 8

#define PIXEL16_RGB565		PIXEL_RGB565 * 16
#define PIXEL16_UYVY		PIXEL_UYVY * 16
#define PIXEL16_YUYV		PIXEL_YUYV * 16
#define PIXEL16_RGB			PIXEL_RGB * 16
#define PIXEL16_BGR			PIXEL_BGR * 16
#define PIXEL16_RGBX		PIXEL_RGBX * 16

#define	LOCAL_DEBUG 0
#define MAX_FRAME 4
#define PREVIEW_PIXEL_BYTES 4	// RGBA/RGBX
#define FRAME_POOL_SZ MAX_FRAME + 2

#define  LOG_TAG    "From Native"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define UVC_STREAM_EOH (1 << 7)
#define UVC_STREAM_ERR (1 << 6)
#define UVC_STREAM_STI (1 << 5)
#define UVC_STREAM_RES (1 << 4)
#define UVC_STREAM_SCR (1 << 3)
#define UVC_STREAM_PTS (1 << 2)
#define UVC_STREAM_EOF (1 << 1)
#define UVC_STREAM_FID (1 << 0)
#define TAG "LibUsb"


#define nullptr ((void*)0)


// see 10918-1:1994, K.3.3.1 Specification of typical tables for DC difference coding
static const unsigned char mjpgHuffmanTable[] = {
        0xff,  0xc4,  0x01,  0xa2,  0x00,  0x00,  0x01,  0x05,  0x01,  0x01,
        0x01,  0x01,  0x01,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
        0x00,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,  0x06,  0x07,  0x08,
        0x09,  0x0a,  0x0b,  0x10,  0x00,  0x02,  0x01,  0x03,  0x03,  0x02,
        0x04,  0x03,  0x05,  0x05,  0x04,  0x04,  0x00,  0x00,  0x01,  0x7d,
        0x01,  0x02,  0x03,  0x00,  0x04,  0x11,  0x05,  0x12,  0x21,  0x31,
        0x41,  0x06,  0x13,  0x51,  0x61,  0x07,  0x22,  0x71,  0x14,  0x32,
        0x81,  0x91,  0xa1,  0x08,  0x23,  0x42,  0xb1,  0xc1,  0x15,  0x52,
        0xd1,  0xf0,  0x24,  0x33,  0x62,  0x72,  0x82,  0x09,  0x0a,  0x16,
        0x17,  0x18,  0x19,  0x1a,  0x25,  0x26,  0x27,  0x28,  0x29,  0x2a,
        0x34,  0x35,  0x36,  0x37,  0x38,  0x39,  0x3a,  0x43,  0x44,  0x45,
        0x46,  0x47,  0x48,  0x49,  0x4a,  0x53,  0x54,  0x55,  0x56,  0x57,
        0x58,  0x59,  0x5a,  0x63,  0x64,  0x65,  0x66,  0x67,  0x68,  0x69,
        0x6a,  0x73,  0x74,  0x75,  0x76,  0x77,  0x78,  0x79,  0x7a,  0x83,
        0x84,  0x85,  0x86,  0x87,  0x88,  0x89,  0x8a,  0x92,  0x93,  0x94,
        0x95,  0x96,  0x97,  0x98,  0x99,  0x9a,  0xa2,  0xa3,  0xa4,  0xa5,
        0xa6,  0xa7,  0xa8,  0xa9,  0xaa,  0xb2,  0xb3,  0xb4,  0xb5,  0xb6,
        0xb7,  0xb8,  0xb9,  0xba,  0xc2,  0xc3,  0xc4,  0xc5,  0xc6,  0xc7,
        0xc8,  0xc9,  0xca,  0xd2,  0xd3,  0xd4,  0xd5,  0xd6,  0xd7,  0xd8,
        0xd9,  0xda,  0xe1,  0xe2,  0xe3,  0xe4,  0xe5,  0xe6,  0xe7,  0xe8,
        0xe9,  0xea,  0xf1,  0xf2,  0xf3,  0xf4,  0xf5,  0xf6,  0xf7,  0xf8,
        0xf9,  0xfa,  0x01,  0x00,  0x03,  0x01,  0x01,  0x01,  0x01,  0x01,
        0x01,  0x01,  0x01,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
        0x01,  0x02,  0x03,  0x04,  0x05,  0x06,  0x07,  0x08,  0x09,  0x0a,
        0x0b,  0x11,  0x00,  0x02,  0x01,  0x02,  0x04,  0x04,  0x03,  0x04,
        0x07,  0x05,  0x04,  0x04,  0x00,  0x01,  0x02,  0x77,  0x00,  0x01,
        0x02,  0x03,  0x11,  0x04,  0x05,  0x21,  0x31,  0x06,  0x12,  0x41,
        0x51,  0x07,  0x61,  0x71,  0x13,  0x22,  0x32,  0x81,  0x08,  0x14,
        0x42,  0x91,  0xa1,  0xb1,  0xc1,  0x09,  0x23,  0x33,  0x52,  0xf0,
        0x15,  0x62,  0x72,  0xd1,  0x0a,  0x16,  0x24,  0x34,  0xe1,  0x25,
        0xf1,  0x17,  0x18,  0x19,  0x1a,  0x26,  0x27,  0x28,  0x29,  0x2a,
        0x35,  0x36,  0x37,  0x38,  0x39,  0x3a,  0x43,  0x44,  0x45,  0x46,
        0x47,  0x48,  0x49,  0x4a,  0x53,  0x54,  0x55,  0x56,  0x57,  0x58,
        0x59,  0x5a,  0x63,  0x64,  0x65,  0x66,  0x67,  0x68,  0x69,  0x6a,
        0x73,  0x74,  0x75,  0x76,  0x77,  0x78,  0x79,  0x7a,  0x82,  0x83,
        0x84,  0x85,  0x86,  0x87,  0x88,  0x89,  0x8a,  0x92,  0x93,  0x94,
        0x95,  0x96,  0x97,  0x98,  0x99,  0x9a,  0xa2,  0xa3,  0xa4,  0xa5,
        0xa6,  0xa7,  0xa8,  0xa9,  0xaa,  0xb2,  0xb3,  0xb4,  0xb5,  0xb6,
        0xb7,  0xb8,  0xb9,  0xba,  0xc2,  0xc3,  0xc4,  0xc5,  0xc6,  0xc7,
        0xc8,  0xc9,  0xca,  0xd2,  0xd3,  0xd4,  0xd5,  0xd6,  0xd7,  0xd8,
        0xd9,  0xda,  0xe2,  0xe3,  0xe4,  0xe5,  0xe6,  0xe7,  0xe8,  0xe9,
        0xea,  0xf2,  0xf3,  0xf4,  0xf5,  0xf6,  0xf7,  0xf8,  0xf9,  0xfa};


#define		LIKELY(x)					((__builtin_expect(!!(x), 1)))	// x is likely true
#define		UNLIKELY(x)					((__builtin_expect(!!(x), 0)))	// x is likely false

#define IYUYV2RGBX_2(pyuv, prgbx, ax, bx) { \
		const int d1 = (pyuv)[ax+1]; \
		const int d3 = (pyuv)[ax+3]; \
		const int r = (22987 * (d3/*(pyuv)[ax+3]*/ - 128)) >> 14; \
		const int g = (-5636 * (d1/*(pyuv)[ax+1]*/ - 128) - 11698 * (d3/*(pyuv)[ax+3]*/ - 128)) >> 14; \
		const int b = (29049 * (d1/*(pyuv)[ax+1]*/ - 128)) >> 14; \
		const int y0 = (pyuv)[ax+0]; \
		(prgbx)[bx+0] = sat(y0 + r); \
		(prgbx)[bx+1] = sat(y0 + g); \
		(prgbx)[bx+2] = sat(y0 + b); \
		(prgbx)[bx+3] = 0xff; \
		const int y2 = (pyuv)[ax+2]; \
		(prgbx)[bx+4] = sat(y2 + r); \
		(prgbx)[bx+5] = sat(y2 + g); \
		(prgbx)[bx+6] = sat(y2 + b); \
		(prgbx)[bx+7] = 0xff; \
    }
#define IYUYV2RGBX_16(pyuv, prgbx, ax, bx) \
	IYUYV2RGBX_8(pyuv, prgbx, ax, bx) \
	IYUYV2RGBX_8(pyuv, prgbx, ax + PIXEL8_YUYV, bx + PIXEL8_RGBX);
#define IYUYV2RGBX_8(pyuv, prgbx, ax, bx) \
	IYUYV2RGBX_4(pyuv, prgbx, ax, bx) \
	IYUYV2RGBX_4(pyuv, prgbx, ax + PIXEL4_YUYV, bx + PIXEL4_RGBX);
#define IYUYV2RGBX_4(pyuv, prgbx, ax, bx) \
	IYUYV2RGBX_2(pyuv, prgbx, ax, bx) \
	IYUYV2RGBX_2(pyuv, prgbx, ax + PIXEL2_YUYV, bx + PIXEL2_RGBX);

#define RGB2RGBX_2(prgb, prgbx, ax, bx) { \
		(prgbx)[bx+0] = (prgb)[ax+0]; \
		(prgbx)[bx+1] = (prgb)[ax+1]; \
		(prgbx)[bx+2] = (prgb)[ax+2]; \
		(prgbx)[bx+3] = 0xff; \
		(prgbx)[bx+4] = (prgb)[ax+3]; \
		(prgbx)[bx+5] = (prgb)[ax+4]; \
		(prgbx)[bx+6] = (prgb)[ax+5]; \
		(prgbx)[bx+7] = 0xff; \
	}
#define RGB2RGBX_16(prgb, prgbx, ax, bx) \
	RGB2RGBX_8(prgb, prgbx, ax, bx) \
	RGB2RGBX_8(prgb, prgbx, ax + PIXEL8_RGB, bx +PIXEL8_RGBX);
#define RGB2RGBX_8(prgb, prgbx, ax, bx) \
	RGB2RGBX_4(prgb, prgbx, ax, bx) \
	RGB2RGBX_4(prgb, prgbx, ax + PIXEL4_RGB, bx + PIXEL4_RGBX);
#define RGB2RGBX_4(prgb, prgbx, ax, bx) \
	RGB2RGBX_2(prgb, prgbx, ax, bx) \
	RGB2RGBX_2(prgb, prgbx, ax + PIXEL2_RGB, bx + PIXEL2_RGBX);

#define MAX_READLINE 8

#ifndef MAX_READLINE
#define MAX_READLINE 1
#endif
#if MAX_READLINE < 1
#undef MAX_READLINE
#define MAX_READLINE 1
#endif

#define IUYVY2RGBX_2(pyuv, prgbx, ax, bx) { \
		const int d0 = (pyuv)[ax+0]; \
		const int d2 = (pyuv)[ax+2]; \
	    const int r = (22987 * (d2/*(pyuv)[ax+2]*/ - 128)) >> 14; \
	    const int g = (-5636 * (d0/*(pyuv)[ax+0]*/ - 128) - 11698 * (d2/*(pyuv)[ax+2]*/ - 128)) >> 14; \
	    const int b = (29049 * (d0/*(pyuv)[ax+0]*/ - 128)) >> 14; \
		const int y1 = (pyuv)[ax+1]; \
		(prgbx)[bx+0] = sat(y1 + r); \
		(prgbx)[bx+1] = sat(y1 + g); \
		(prgbx)[bx+2] = sat(y1 + b); \
		(prgbx)[bx+3] = 0xff; \
		const int y3 = (pyuv)[ax+3]; \
		(prgbx)[bx+4] = sat(y3 + r); \
		(prgbx)[bx+5] = sat(y3 + g); \
		(prgbx)[bx+6] = sat(y3 + b); \
		(prgbx)[bx+7] = 0xff; \
    }
#define IUYVY2RGBX_16(pyuv, prgbx, ax, bx) \
	IUYVY2RGBX_8(pyuv, prgbx, ax, bx) \
	IUYVY2RGBX_8(pyuv, prgbx, ax + PIXEL8_UYVY, bx + PIXEL8_RGBX)
#define IUYVY2RGBX_8(pyuv, prgbx, ax, bx) \
	IUYVY2RGBX_4(pyuv, prgbx, ax, bx) \
	IUYVY2RGBX_4(pyuv, prgbx, ax + PIXEL4_UYVY, bx + PIXEL4_RGBX)
#define IUYVY2RGBX_4(pyuv, prgbx, ax, bx) \
	IUYVY2RGBX_2(pyuv, prgbx, ax, bx) \
	IUYVY2RGBX_2(pyuv, prgbx, ax + PIXEL2_UYVY, bx + PIXEL2_RGBX)
#define IUYVY2RGB_8(pyuv, prgb, ax, bx) \
	IUYVY2RGB_4(pyuv, prgb, ax, bx) \
	IUYVY2RGB_4(pyuv, prgb, ax + 8, bx + 12)
#define IUYVY2RGB_4(pyuv, prgb, ax, bx) \
	IUYVY2RGB_2(pyuv, prgb, ax, bx) \
	IUYVY2RGB_2(pyuv, prgb, ax + 4, bx + 6)
#define IYUYV2RGB_2(pyuv, prgb, ax, bx) { \
		const int d1 = (pyuv)[ax+1]; \
		const int d3 = (pyuv)[ax+3]; \
		const int r = (22987 * (d3/*(pyuv)[ax+3]*/ - 128)) >> 14; \
		const int g = (-5636 * (d1/*(pyuv)[ax+1]*/ - 128) - 11698 * (d3/*(pyuv)[ax+3]*/ - 128)) >> 14; \
		const int b = (29049 * (d1/*(pyuv)[ax+1]*/ - 128)) >> 14; \
		const int y0 = (pyuv)[ax+0]; \
		(prgb)[bx+0] = sat(y0 + r); \
		(prgb)[bx+1] = sat(y0 + g); \
		(prgb)[bx+2] = sat(y0 + b); \
		const int y2 = (pyuv)[ax+2]; \
		(prgb)[bx+3] = sat(y2 + r); \
		(prgb)[bx+4] = sat(y2 + g); \
		(prgb)[bx+5] = sat(y2 + b); \
    }
#define IUYVY2RGB_2(pyuv, prgb, ax, bx) { \
		const int d0 = (pyuv)[ax+0]; \
		const int d2 = (pyuv)[ax+2]; \
	    const int r = (22987 * (d2/*(pyuv)[ax+2]*/ - 128)) >> 14; \
	    const int g = (-5636 * (d0/*(pyuv)[ax+0]*/ - 128) - 11698 * (d2/*(pyuv)[ax+2]*/ - 128)) >> 14; \
	    const int b = (29049 * (d0/*(pyuv)[ax+0]*/ - 128)) >> 14; \
		const int y1 = (pyuv)[ax+1]; \
		(prgb)[bx+0] = sat(y1 + r); \
		(prgb)[bx+1] = sat(y1 + g); \
		(prgb)[bx+2] = sat(y1 + b); \
		const int y3 = (pyuv)[ax+3]; \
		(prgb)[bx+3] = sat(y3 + r); \
		(prgb)[bx+4] = sat(y3 + g); \
		(prgb)[bx+5] = sat(y3 + b); \
    }
#define IYUYV2RGB_16(pyuv, prgb, ax, bx) \
	IYUYV2RGB_8(pyuv, prgb, ax, bx) \
	IYUYV2RGB_8(pyuv, prgb, ax + PIXEL8_YUYV, bx + PIXEL8_RGB)
#define IYUYV2RGB_8(pyuv, prgb, ax, bx) \
	IYUYV2RGB_4(pyuv, prgb, ax, bx) \
	IYUYV2RGB_4(pyuv, prgb, ax + PIXEL4_YUYV, bx + PIXEL4_RGB)
#define IYUYV2RGB_4(pyuv, prgb, ax, bx) \
	IYUYV2RGB_2(pyuv, prgb, ax, bx) \
	IYUYV2RGB_2(pyuv, prgb, ax + PIXEL2_YUYV, bx + PIXEL2_RGB)


struct uvc_stream_handle {
	//struct uvc_device_handle *devh;
	//struct uvc_stream_handle *prev, *next;
	//struct uvc_streaming_interface *stream_if;

	/** if true, stream is running (streaming video to host) */
	uint8_t running;
	/** Current control block */
	//struct uvc_stream_ctrl cur_ctrl;

	/* listeners may only access hold*, and only when holding a
     * lock on cb_mutex (probably signaled with cb_cond) */
	uint8_t bfh_err, hold_bfh_err;	// XXX added to keep UVC_STREAM_ERR
	uint8_t fid;
	uint32_t seq, hold_seq;
	uint32_t pts, hold_pts;
	uint32_t last_scr, hold_last_scr;
	size_t got_bytes, hold_bytes;
	size_t size_buf;	// XXX add for boundary check
	uint8_t *outbuf, *holdbuf;
	pthread_mutex_t cb_mutex;
	pthread_cond_t cb_cond;
	pthread_t cb_thread;
	uint32_t last_polled_seq;
	//uvc_frame_callback_t *user_cb;
	void *user_ptr;
	//struct libusb_transfer *transfers[LIBUVC_NUM_TRANSFER_BUFS];
	//uint8_t *transfer_bufs[LIBUVC_NUM_TRANSFER_BUFS];
	//struct uvc_frame frame;
	enum uvc_frame_format frame_format;
};
typedef struct uvc_stream_handle uvc_stream_handle_t;

/** Context within which we communicate with devices */
struct uvc_context {
	/** Underlying context for USB communication */
	struct libusb_context *usb_ctx;
	/** True if libuvc initialized the underlying USB context */
	uint8_t own_usb_ctx;
	/** List of open devices in this context */
	//uvc_device_handle_t *open_devices;
	pthread_t handler_thread;
	uint8_t kill_handler_thread;
};
typedef struct uvc_context uvc_context_t;


/** Handle on an open UVC device
 *
 * @todo move most of this into a uvc_device struct?
 */
struct uvc_device_handle {
    struct uvc_device *dev;
    struct uvc_device_handle *prev, *next;
    /** Underlying USB device handle */
    libusb_device_handle *usb_devh;
    //struct uvc_device_info *info;
    //struct libusb_transfer *status_xfer;
    pthread_mutex_t status_mutex;	// XXX saki
    uint8_t status_buf[32];
    /** Function to call when we receive status updates from the camera */
    //uvc_status_callback_t *status_cb;
    void *status_user_ptr;
    /* Function to call when we receive button events from the camera */
    //uvc_button_callback_t *button_cb;
    void *button_user_ptr;

    uvc_stream_handle_t *streams;
    /** Whether the camera is an iSight that sends one header per frame */
    uint8_t is_isight;
    uint8_t reset_on_release_if;	// XXX whether interface alt setting needs to reset to 0.
};
typedef struct uvc_device_handle uvc_device_handle_t;


/** An image frame received from the UVC device
 * @ingroup streaming
 */
typedef struct uvc_frame {
    /** Image data for this frame */
    void *data;
    /** Size of image data buffer */
    size_t data_bytes;
    /** XXX Size of actual received data to confirm whether the received bytes is same
     * as expected on user function when some microframes dropped */
    size_t actual_bytes;
    /** Width of image in pixels */
    uint32_t width;
    /** Height of image in pixels */
    uint32_t height;
    /** Pixel data format */
    enum uvc_frame_format frame_format;
    /** Number of bytes per horizontal line (undefined for compressed format) */
    size_t step;
    /** Frame number (may skip, but is strictly monotonically increasing) */
    uint32_t sequence;
    /** Estimate of system time when the device started capturing the image */
    struct timeval capture_time;
    /** Handle on the device that produced the image.
     * @warning You must not call any uvc_* functions during a callback. */
    uvc_device_handle_t *source;
    /** Is the data buffer owned by the library?
     * If 1, the data buffer can be arbitrarily reallocated by frame conversion
     * functions.
     * If 0, the data buffer will not be reallocated or freed by the library.
     * Set this field to zero if you are supplying the buffer.
     */
    uint8_t library_owns_data;
} uvc_frame_t;


struct uvc_device {
    struct uvc_context *ctx;
    int ref;
    libusb_device *usb_dev;
};
typedef struct uvc_device uvc_device_t;


  #endif  // iso_h__

