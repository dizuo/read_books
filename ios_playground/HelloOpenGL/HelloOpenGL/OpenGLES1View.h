//
//  OpenGLES1.h
//  HelloOpenGL
//
//  Created by peteryfren on 15/4/17.
//  Copyright (c) 2015年 peteryfren. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include<OpenGLES/ES1/gl.h>
#include<OpenGLES/ES1/glext.h>

@interface OpenGLES1View : UIView {
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    GLuint _colorRenderBuffer;
    
    GLuint _positionSlot;
    GLuint _colorSlot;
    
}

@end
