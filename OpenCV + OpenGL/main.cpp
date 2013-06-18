#include <opencv2/opencv.hpp>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <cstdio>

cv::VideoCapture *cap = NULL;
int width = 640;
int height = 480;
cv::Mat image;


GLuint texture[1];

double angle = 0;

typedef struct
{
    
    int X;
    
    int Y;
    
    int Z;
    
    
    
    double U;
    
    double V;
}VERTICES;

const double PI = 3.1415926535897;

const int space = 10;

const int VertexCount = (90 / space) * (360 / space) * 4;

VERTICES VERTEX[VertexCount];

GLuint LoadTextureRAW( const char * filename );




void DisplaySphere (double R, GLuint texture){
    
    int b;
    
    
    
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);
    
    
    
    glRotatef (90, 1, 0, 0);
    
    
    
    glBindTexture (GL_TEXTURE_2D, texture);
    
    
    
    glBegin (GL_TRIANGLE_STRIP);
    
    for ( b = 0; b <= VertexCount; b++){
        
        glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
        
    }
    
    
    
    for ( b = 0; b <= VertexCount; b++){
        
        glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);
        
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
        
    }
    
    glEnd();
}


void CreateSphere (double R, double H, double K, double Z) {
    
    int n;
    
    double a;
    
    double b;
    
    
    
    n = 0;
    
    
    
    for( b = 0; b <= 90 - space; b+=space){
        
        for( a = 0; a <= 360 - space; a+=space){
            
            
            
            VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
            
            VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
            
            VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
            
            VERTEX[n].V = (2 * b) / 360;
            
            VERTEX[n].U = (a) / 360;
            
            n++;
            
            
            
            VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI
                                                        
                                                        ) - H;
            
            VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI
                                                        
                                                        ) + K;
            
            VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
            
            VERTEX[n].V = (2 * (b + space)) / 360;
            
            VERTEX[n].U = (a) / 360;
            
            n++;
            
            
            
            VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI
                                                                
                                                                ) - H;
            
            VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI
                                                                
                                                                ) + K;
            
            VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
            
            VERTEX[n].V = (2 * b) / 360;
            
            VERTEX[n].U = (a + space) / 360;
            
            n++;
            
            
            
            VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) /
                                                                
                                                                180 * PI) - H;
            
            VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) /
                                                                
                                                                180 * PI) + K;
            
            VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
            
            VERTEX[n].V = (2 * (b + space)) / 360;
            
            VERTEX[n].U = (a + space) / 360;
            
            n++;
            
            
            
        }
        
    }
}

void display()
{
    // clear the window
    glClear( GL_COLOR_BUFFER_BIT );
    
    // show the current camera frame
    
    //based on the way cv::Mat stores data, you need to flip it before displaying it
    cv::Mat tempimage;
    cv::flip(image, tempimage, 0);
    glDrawPixels( tempimage.size().width, tempimage.size().height, GL_BGR, GL_UNSIGNED_BYTE, tempimage.ptr() );
    
    //////////////////////////////////////////////////////////////////////////////////
    // Here, set up new parameters to render a scene viewed from the camera.
    
    //set viewport
    glViewport(0, 0, tempimage.size().width, tempimage.size().height);
    
    //set projection matrix using intrinsic camera params
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective is arbitrarily set, you will have to determine these values based
    //on the intrinsic camera parameters
    gluPerspective(60, tempimage.size().width*1.0/tempimage.size().height, 1, 20);
    
    //you will have to set modelview matrix using extrinsic camera params
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    
    
    /////////////////////////////////////////////////////////////////////////////////
    // Drawing routine
    
    //now that the camera params have been set, draw your 3D shapes
    //first, save the current matrix
    glPushMatrix();
    
    glTranslatef(0,0,0);
    
    
    
    glRotatef(angle,0,1,0);
    
    DisplaySphere(1, texture[0]);
    //move to the position where you want the 3D object to go
    //glutSolidSphere(.3, 100, 100);
    glPopMatrix();
    
    
    // show the rendering on the screen
    glutSwapBuffers();
    angle++;
    // post the next redisplay
    glutPostRedisplay();
}


void init (void) {
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable( GL_TEXTURE_2D );
    
    glDepthFunc(GL_LEQUAL);
    
    glCullFace(GL_BACK);
    
    glFrontFace(GL_CCW);
    
    glEnable(GL_CULL_FACE);
    
    texture[0] = LoadTextureRAW( "/Users/PabloHolanda/Downloads/earth.raw");
    
    CreateSphere(70,0,0,0);
}

void reshape( int w, int h )
{
    // set OpenGL viewport (drawable area)
    glViewport( 0, 0, w, h );
    
}

void mouse( int button, int state, int x, int y )
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
    {
        
    }
}

void keyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'q':
            // quit when q is pressed
            exit(0);
            break;
            
        default:
            break;
    }
}

void idle()
{
    // grab a frame from the camera
    (*cap) >> image;
}

int main( int argc, char **argv )
{
    int w,h;
    
    if ( argc == 1 ) {
        // start video capture from camera
        cap = new cv::VideoCapture(0);
    } else if ( argc == 2 ) {
        // start video capture from file
        cap = new cv::VideoCapture(argv[1]);
    } else {
        fprintf( stderr, "usage: %s [<filename>]\n", argv[0] );
        return 1;
    }
    
    // check that video is opened
    if ( cap == NULL || !cap->isOpened() ) {
        fprintf( stderr, "could not start video capture\n" );
        return 1;
    }
    
    // get width and height
    w = (int) cap->get( CV_CAP_PROP_FRAME_WIDTH );
    h = (int) cap->get( CV_CAP_PROP_FRAME_HEIGHT );
    // On Linux, there is currently a bug in OpenCV that returns
    // zero for both width and height here (at least for video from file)
    // hence the following override to global variable defaults:
    width = w ? w : width;
    height = h ? h : height;
    
    // initialize GLUT
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowPosition( 20, 20 );
    glutInitWindowSize( width, height );
    glutCreateWindow( "OpenGL / OpenCV Example" );
    init();
    // set up GUI callback functions
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutMouseFunc( mouse );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    
    // start GUI loop
    glutMainLoop();
    
    return 0;
}

GLuint LoadTextureRAW( const char * filename )
{
    
    GLuint texture;
    
    int width, height;
    
    unsigned char * data;
    
    FILE * file;
    
    
    
    file = fopen( filename, "rb" );
    
    if ( file == NULL ) return 0;
    
    
    
    width = 1024;
    
    height = 512;
    
    data = (unsigned char *)malloc( width * height * 3 );
    
    
    
    fread( data, width * height * 3, 1, file );
    
    fclose( file );
    
    
    
    glGenTextures( 1, &texture );
    
    
    
    glBindTexture( GL_TEXTURE_2D, texture );
    
    
    
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
              
              GL_MODULATE );
    
    
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    
                    GL_LINEAR_MIPMAP_NEAREST );
    
    
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    
                    GL_LINEAR );
    
    
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    
                    GL_REPEAT );
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    
                    GL_REPEAT );
    
    
    
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                      
                      GL_RGB, GL_UNSIGNED_BYTE, data );
    
    
    
    free( data );
    
    
    
    return texture;
    
    
}
