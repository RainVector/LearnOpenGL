#ifndef COMMON_H
#define COMMON_H
//rendering mode
extern int rendermode;
#define OBJMESHRENDER_VERTEX                (0)             //只渲染顶点
#define OBJMESHRENDER_TRIANGLE              (1 << 0)       //三角网格
#define OBJMESHRENDER_TEXTURE               (1 << 1)       //加上纹理


#endif // !COMMON_H
