//
//  LXPointMetrix.c
//  CharaterText
//
//  Created by Vincent Wang on 2016/11/16.
//  Copyright © 2016年 subvin.inc. All rights reserved.
//

#include "LXPointMetrix.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include <iconv.h>
#include <stdlib.h>
#define OUTLEN 255


//const char * path = "HZK16";


uint8_t * pointMetrix( const char * path,const char * text)
{
    char chs[32];
    FILE *fp;
    int i,j;
    long offset;
    unsigned char qh,wh;   //  qh  Unicode string  区号    wh  Unicode string 位号
    
    uint8_t *metrix = (uint8_t *)malloc(sizeof(uint8_t) * 256);
    
    printf("text address == %p   text == %s\n",&text,text);
    
    printf("strlen text == %d",(int)strlen(text));
    
    if ((fp=fopen(path,"r"))==NULL)
        
        return NULL;
    
    for (int k = 0; k < strlen(text); k += 3 ) {
        
        qh = text[k] - 0xa0 ; //获取区码
        wh = text[ k + 1] - 0xa0 ; //获取位码
        
        offset=((qh - 1) * 94 + (wh - 1)) * 32;  //根据内码找出汉字在HZK16中的偏移位置
        
        fseek(fp,offset,SEEK_SET);
        
        fread(chs,32,1,fp);
        
        for (i=0;i<32;i++)
        {
            if (i%2==0)
                printf("\n");   //每行两字节,16X16点阵
            for (j=7;j>=0;j--)
            {
                if (chs[i]&(0x01<<j))
                {
                    printf("."); //由高到低,为1则输出'字',反之输出' ';
                    metrix[ i * 8 +( 7 - j)] = 1;
                }
                else{
                    
                    printf(" ");
                    metrix[ i * 8 +( 7 - j)] = 0;
                }
                
            }
        }
        printf("\n\n");
    }
    fclose(fp);
    return metrix;
}


