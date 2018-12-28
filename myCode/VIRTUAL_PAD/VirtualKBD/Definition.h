/* 
 * File:   Definition.h
 * Author: Tinker Han
 *
 * Created on 2018年5月2日, 下午4:53
 */

#ifndef DEFINITION_H
#define DEFINITION_H

#define RGB(r,g,b)                  ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define FLIGHTGRAY_COLOR            (RGB(211, 211, 211))
#define BLACK_COLOR                 (RGB(0, 0, 0))
#define WHITE_COLOR                 (RGB(255, 255, 255))
#define GREY_COLOR                  (RGB(190, 190, 190))
#define GREEN_COLOR                 (RGB(0, 255, 127))
#define BLUE_COLOR                  (RGB(0, 255, 255))
#define INVALID_THREAD_ID           (-1)
#define TOUCH_DEVICE_NAME           "/dev/input/event0"
#define INVALID_TOUCH_DEV_HANDLE    (-1)
#define EVT_BUF_COUNT               (5)
#define TouchEventSize              (10)
#define DisplayColumn_MAXLEN        (18)
#define CHOOSE_CAPTION_TIMEOUT      (100)

/***************************************SCOPE JUDGMENT***************************************/
#define SCOPE_VALID(x, y)            ((x >= 0) && (x <= 320) && (y >= 280) && (y <= 480))
#define SCOPE_INVALID(x, y)          ((x >= 0) && (x <= 320) && (y >= 0) && (y <= 280))

#define SCOPE_LN1_COL1(x, y)         ((x >= 0) && (x <= 80) && (y >= 280) && (y <= 320))
#define SCOPE_LN1_COL2(x, y)         ((x >= 80) && (x <= 160) && (y >= 280) && (y <= 320))
#define SCOPE_LN1_COL3(x, y)         ((x >= 160) && (x <= 240) && (y >= 280) && (y <= 320))

#define SCOPE_LN2_COL1(x, y)         ((x >= 0) && (x <= 80) && (y >= 320) && (y <= 370))
#define SCOPE_LN2_COL2(x, y)         ((x >= 80) && (x <= 160) && (y >= 320) && (y <= 370))
#define SCOPE_LN2_COL3(x, y)         ((x >= 160) && (x <= 240) && (y >= 320) && (y <= 370))

#define SCOPE_LN3_COL1(x, y)         ((x >= 0) && (x <= 80) && (y >= 370) && (y <= 430))
#define SCOPE_LN3_COL2(x, y)         ((x >= 80) && (x <= 160) && (y >= 370) && (y <= 430))
#define SCOPE_LN3_COL3(x, y)         ((x >= 160) && (x <= 240) && (y >= 370) && (y <= 430))

#define SCOPE_LN4_COL1(x, y)         ((x >= 0) && (x <= 80) && (y >= 430) && (y <= 480))
#define SCOPE_LN4_COL2(x, y)         ((x >= 80) && (x <= 160) && (y >= 430) && (y <= 480))
#define SCOPE_LN4_COL3(x, y)         ((x >= 160) && (x <= 240) && (y >= 430) && (y <= 480))

#define SCOPE_CANCEL(x, y)           ((x >= 240) && (x <= 320) && (y >= 280) && (y <= 330))
#define SCOPE_CLEAR(x, y)            ((x >= 240) && (x <= 320) && (y >= 330) && (y <= 380))
#define SCOPE_ENTER(x, y)            ((x >= 240) && (x <= 320) && (y >= 380) && (y <= 480))

#define SCOPE_CN_L(x, y)             ((x >= 0) && (x <= 80) && (y >= 280) && (y <= 380))
#define SCOPE_CN_M(x, y)             ((x >= 80) && (x <= 160) && (y >= 280) && (y <= 380))
#define SCOPE_CN_R(x, y)             ((x >= 160) && (x <= 240) && (y >= 280) && (y <= 380))
#define SCOPE_NONSELECTIVE(x, y)     ((x >= 0) && (x <= 240) && (y >= 380) && (y <= 480))

/*************************************SCOPE DEFINE******************************************/
//parent interface
////////////////////////////////////////////////
//    1    //    2    //     3    //  cancel  //
//         //         //          //          //
////////////////////////////////////////////////
//    4    //    5    //     6    //  clear   //
//         //         //          //          //
////////////////////////////////////////////////
//    7    //    8    //     9    //          //
//         //         //          //          //
////////////////////////////////////  enter   //
//  switch //    0    //   cap    //          //
//         //         //          //          //
////////////////////////////////////////////////

#define SCOPE_PARENT_0                      (0x00)
#define SCOPE_PARENT_1                      (0x01)
#define SCOPE_PARENT_2                      (0x02)
#define SCOPE_PARENT_3                      (0x03)
#define SCOPE_PARENT_4                      (0x04)
#define SCOPE_PARENT_5                      (0x05)
#define SCOPE_PARENT_6                      (0x06)
#define SCOPE_PARENT_7                      (0x07)
#define SCOPE_PARENT_8                      (0x08)
#define SCOPE_PARENT_9                      (0x09)
#define SCOPE_PARENT_CAP                    (0x0a)
#define SCOPE_PARENT_SWITCH                 (0x0b)

#define SCOPE_FUNC_CANCEL                   (0x0c)
#define SCOPE_FUNC_CLEAR                    (0x0d)
#define SCOPE_FUNC_ENTER                    (0x0e)
#define SCOPE_FUNC_HIDE                     (0x0f)

//Touch not detected
#define SCOPE_VOID                          (0xff)

//child interface
////////////////////////////////////////////////
//         //         //          //  cancel  //
//         //         //          //          //
//  left   //   mid   //  right   //////////////
//         //         //          //   clear  //
//         //         //          //          //
////////////////////////////////////////////////
//                                //          //
//                                //          //
//           invalid              //   enter  //
//                                //          //
//                                //          //
////////////////////////////////////////////////

#define SCOPE_CHILD_LEFT                    (0x10)
#define SCOPE_CHILD_MID                     (0x11)
#define SCOPE_CHILD_RIGHT                   (0x12)
#define SCOPE_CHILD_INVALID                 (0x13)

#endif /* DEFINITION_H */

