//
//  OpenGLES1.m
//  HelloOpenGL
//
//  Created by peteryfren on 15/4/17.
//  Copyright (c) 2015年 peteryfren. All rights reserved.
//

#import "OpenGLES1View.h"

@implementation OpenGLES1View

+(Class)layerClass {
    return [CAEAGLLayer class];
}

-(void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

-(void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES1;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 1.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupRenderBuffer {
    glGenRenderbuffersOES(1, &_colorRenderBuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:_eaglLayer];
}

- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffersOES(1, &framebuffer);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, framebuffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,
                              GL_RENDERBUFFER_OES, _colorRenderBuffer);
}

void glx_Perspective( GLfloat fov, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar )
{
    // 使用glu库函数，需要添加glu.h头文件
    //gluPerspective( fov, aspectRatio, zNear, zFar );
    
    
    // 使用OpenGL函数，但是需要添加math.h头文件
    GLfloat rFov = fov * 3.14159265 / 180.0;
    glFrustumf( -zNear * tan( rFov / 2.0 ) * aspectRatio,
              zNear * tan( rFov / 2.0 ) * aspectRatio,
              -zNear * tan( rFov / 2.0 ),
              zNear * tan( rFov / 2.0 ),
              zNear, zFar );
}

- (void)render {
    float gray = 104.0/255.0;
    
    glClearDepthf(0.0f);
    glClearColor(gray, gray, gray, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float width = self.frame.size.width;
    float height = self.frame.size.height;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glx_Perspective(60.0, width/height, 0.001, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -10);
    
    glColor4f(0, 0, 1, 1);
    GLfloat vertices[] = { -1,-1,0, -1,1,0, 1,1,0, 1,-1,0 };
    GLubyte indices [] = {0, 1, 2, 0, 2, 3};
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
    
    int error = glGetError();
    if (error != 0)
        printf("error = %d\n", error);
    
    [_context presentRenderbuffer:GL_RENDERBUFFER_OES];
}

// Replace initWithFrame with this
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        
        [self render];
    }
    return self;
}

@end
