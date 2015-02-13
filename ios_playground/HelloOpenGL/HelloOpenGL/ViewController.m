//
//  ViewController.m
//  HelloOpenGL
//
//  Created by peteryfren on 15/2/12.
//  Copyright (c) 2015年 peteryfren. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.glView =  [[OpenGLView alloc] initWithFrame:self.view.bounds];
    //[self.view addSubview: _glView];  // 添加单个view
    
    [self.view insertSubview:_glView belowSubview:_button]; // add glview bellow button.
    
    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleClick)];
    gesture.numberOfTapsRequired = 2;
    [self.view addGestureRecognizer:gesture];
    
    UIPanGestureRecognizer *panGes = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
    [self.view addGestureRecognizer:panGes];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)handlePan:(UIPanGestureRecognizer *)recognizer {
    CGPoint offPoint = [recognizer translationInView:self.view];
    NSLog(@"gesture translated point is %@", NSStringFromCGPoint(offPoint));
    
    if ([recognizer state] == UIGestureRecognizerStateBegan) {
        NSLog(@"begin pan");
    }
    
    if ([recognizer state] == UIGestureRecognizerStateChanged) {
        NSLog(@"paning");
    }
    
    // ref http://blog.csdn.net/mikixiyou/article/details/9341195
}


- (void)singleClick
{
    NSLog(@"single click\n");
}

- (IBAction)zoomIn:(id)sender {
    printf("zoom in\n");
}


@end
