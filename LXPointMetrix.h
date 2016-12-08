//
//  LXPointMetrix.h
//  CharaterText
//
//  Created by Vincent Wang on 2016/11/16.
//  Copyright © 2016年 subvin.inc. All rights reserved.
//

#ifndef LXPointMetrix_h
#define LXPointMetrix_h

#include <stdbool.h>
#include <stdio.h>
#include <iconv.h>
#include <stdlib.h>

struct LXWorld{
    bool isHanWorld;  //  是汉字则返回   16 *  16 的方阵   是  字母 则返回  16 * 8 的矩形 阵
    uint8_t *worldMetrix;
    struct LXWorld *next;
};

//  多字节操作
struct LXWorld * analysisString( const char * hzk16Path , const char * asc16Path, const unsigned char * text);

// 单字解析 返回  16 * 16的数组
uint8_t * singleWordPointMetrix( const char * hzk16Path , const char * asc16Path, const unsigned char * text);

//uint8_t * pointMetrix( const char * hzk16Path , const char * asc16Path, const unsigned char * text);


#endif /* LXPointMetrix_h */
