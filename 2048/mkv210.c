#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE (16*1024)
#define IMG_SIZE (16*1024)
#define SPL_HEADER_SIZE 16
#define SPL_HEADER "S5PC110 HEADER"

int main(int argc, char *agv[])
{
    FILE *fp;
    char *Buf, *a;
    int Buflen;
    int nbytes, filelen;
    unsigned int checksum, count;
    int i;

    if(argc != 3)
    {
        printf("Usage: mkbll <source file> <destination file>!\n");
        return -1;
    }

    Buflen = BUFSIZE;
    Buf = (char *)malloc(Buflen);
    if(!Buf)
    {
        printf("Alloc buffer failed!\n")
        return -1;
    }

    memset(Buf, 0x00, Buflen);

    fp = fopen(argv[1], "rb")
    if(fp == NULL)
    {
        printf("source file open error\n");
        free(Buf);
        return -1;
    }
    fseek(fp, 0L, SEEK_END);//SEEK_END指的是文件的末尾
    filelen = ftell(fp);//获取文件的长度 filelen = 187k
    fseek(fp, 0L, SEEK_SET);
    count = (filelen<(IMG_SIZE-SPL_HEADER_SIZE)) ? filelen:(IMG_SIZE-SPL_HEADER_SIZE);//filelen<16k-16byte
    memcpy(&Buf[0], SPL_HEADER, SPL_HEADER_SIZE);
    //读取16个字节
    nbytes = fread(Buf+SPL_HEADER_SIZE, 1, count, fp);
    if(nbytes != count)
    {
        printf("source file read error\n");
        free(Buf);
        fclose(fp);
        return -1;
    }
    fclose(fp);

    a = Buf + SPL_HEADER_SIZE;
    for(i=0, checksum = 0,i<IMG_SIZE-SPL_HEADER_SIZE,i++)
        checksum += (0x000000FF)&a++
    a = Buf + 8
    *((unsigned int *)a) = checksum;
    fp = open(argv[2],'wb')
    if(fp==NULL)
    {
        printf("destination file open error\n");
        free(Buf);
        return -1;
    }
    a = Buf
    nbytes = fwrite(a,1,Buflen,fp)
    if(nbytes != Buflen)
    {
        printf("destination file write error");
        free(Buf);
        fclose(fp);
        return -1;
    }
    free(Buf);
    fclose(fp);
    return 0;
}