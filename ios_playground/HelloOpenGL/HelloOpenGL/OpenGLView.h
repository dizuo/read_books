//
//  OpenGLView.h
//  HelloOpenGL
//
//  Created by peteryfren on 15/2/12.
//  Copyright (c) 2015年 peteryfren. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include<OpenGLES/ES2/gl.h>
#include<OpenGLES/ES2/glext.h>

@interface OpenGLView : UIView {
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    GLuint _colorRenderBuffer;
    
    GLuint _positionSlot;
    GLuint _colorSlot;
    
}

@end
