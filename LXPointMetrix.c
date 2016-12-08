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


uint8_t * singleWordPointMetrix( const char * hzk16Path , const char * asc16Path, const unsigned char * text)
{
    
    assert(text != NULL);
    
    if( 0 == strlen(text) || !text){
        printf("传入的参数不能为空字符\n");
        return NULL;
    }
    
    char chs[32];
    FILE *fp = NULL;
    int i,j;
    long offset;
    unsigned char qh,wh;   //  qh  Unicode string  区号    wh  Unicode string 位号
    
    uint8_t *metrix = (uint8_t *)malloc(sizeof(uint8_t) * 3200);
    
    printf(" text == %s\n",text);
    
    
    
    
    
    for (int k = 0; k < (int)strlen(text);  ) {
        
        
        
        
        if ( text[ k] <= 0x7a ) {  //   判断是否字母，
            if (( fp = fopen(asc16Path,"r"))==NULL)
                return NULL;
            offset = text[ k ] * AlphabetLength;  //  字母在ASC 16 偏移量的计算公式
            
            fseek(fp,offset,SEEK_SET);
            
            fread(chs,AlphabetLength,1,fp);
            
            for ( i = 0 ; i < HanWordLength ; i++)
            {
                
                if (i % 2 != 0) {
                    
                    for ( j = 7 ; j >= 0 ; j--)
                    {
                        metrix[ i * SingleWordBits + ( 7 - j)] = 0;
                    }
                }else
                {
                    for ( j = 7 ; j >= 0 ; j--)
                    {
                        if (chs[i /2 ]&(0x01<<j))
                        {
                            printf("."); //由高到低,为1则输出'字',反之输出' ';
                            metrix[ i * SingleWordBits + ( 7 - j)] = 1;
                        }else{
                            printf(" ");
                            metrix[ i * SingleWordBits + ( 7 - j)] = 0;
                            metrix[ i * SingleWordBits  + ( 7 - j) + 1] = 0;
                        }
                    }
                }
                printf("\n");
            }
            printf("\n\n");
            k++;
            
        }else
        {
            if (( fp = fopen(hzk16Path,"r"))==NULL)
                return NULL;
            
            qh = text[k ] - Offset ; //获取区码
            wh = text[k + 1] - Offset ; //获取位码
            
            offset = ((wh - 1) + (qh - 1) * 94) * HanWordLength;  //根据内码找出汉字在HZK16中的偏移位置
            
            fseek(fp,offset,SEEK_SET);
            
            fread(chs,HanWordLength,1,fp);
            
            for ( i = 0 ; i < HanWordLength ; i++)
            {
                if ( i%2 == 0)
                    printf("\n");   //每行两字节,16X16点阵
                for ( j = 7 ; j >= 0 ; j--)
                {
                    if ( chs[i] & (0x01 << j ))
                    {
                        printf("."); //由高到低,为1则输出'字',反之输出' ';
                        metrix[ i * SingleWordBits +( 7 - j)] = 1;
                    }
                    else{
                        printf(" ");
                        metrix[ i * SingleWordBits +( 7 - j)] = 0;
                    }
                }
            }
            printf("\n\n");
            k += HanWordBytes;
        }
    }
    fclose(fp);
    return metrix;
}


