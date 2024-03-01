#include "dxf_document.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct __dxf_write {
    FILE        *fp;
    enum Version version;
    dxf_U32      m_handle;
    dxf_U32      modelSpaceHandle;
    dxf_U32      paperSpaceHandle;
    dxf_U32      paperSpace0Handle;
    // document 加进去呢// 此时也在正常些，问题不大，而且外部不知道document
    // 读的时候呢，也是内部去创建一个读的结构体，此时在一个函数里面读，中途调用这个函数
    // 传递的回调函数就行
};