#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include "Serial.h"
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>


using namespace cv;
//inicializar os valores de maximo e minimo para o filtro HSV
//podem ser alterados na barra de calibração
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;
//setar o tamanho da area de captura
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//numero maximo de obejtos que podem ser detectados em um frame
const int MAX_NUM_OBJECTS=50;
//numero minimo e maximo de obejtos por area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//nnomeclatura das janelas
const string windowName = "imagem original";
const string windowName1 = "Imagem HSV";
const string windowName2 = "Imagem com Thresholded";
const string windowName3 = "Após as operações morfológicas";
const string trackbarWindowName = "Trackbars";
void on_trackbar( int, void* )
{
    //essa função é chamada sempre que se é alterado um valor do filtro...
    
}
string intToString(int number){
    
    
	std::stringstream ss;
	ss << number;
	return ss.str();
}
void createTrackbars(){
	//criar a janela para calibração do filtro
    
    
    namedWindow(trackbarWindowName,0);
	//criar uma memoria para armazenar os nomes dos paramentro das barras de ajuste
	char TrackbarName[50];
	sprintf( TrackbarName, "H_MIN", H_MIN);
	sprintf( TrackbarName, "H_MAX", H_MAX);
	sprintf( TrackbarName, "S_MIN", S_MIN);
	sprintf( TrackbarName, "S_MAX", S_MAX);
	sprintf( TrackbarName, "V_MIN", V_MIN);
	sprintf( TrackbarName, "V_MAX", V_MAX);
	//cria a barra e insere na janela
	//sempre que um valor é modificado chama a funcao on_trackbar
    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar );
    
    
}
void drawObject(int x, int y,Mat &frame){
    
	//utilizando algumas das funções do OpenCv para desenhar a mira
	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
	line(frame,Point(x,y-5),Point(x,y-25),Scalar(0,255,0),2);
	line(frame,Point(x,y+5),Point(x,y+25),Scalar(0,255,0),2);
	line(frame,Point(x-5,y),Point(x-25,y),Scalar(0,255,0),2);
	line(frame,Point(x+5,y),Point(x+25,y),Scalar(0,255,0),2);
    
	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
    
    

}
void morphOps(Mat &thresh){
    
    //criar as estruturas que vai dilatar e gerar eroção na imagem
	//o elemento aqui escolhido é um retando de 3px por 3px
    
	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilatar os grandes obejetos para garantir que o objeto esteja visivel
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));
    
	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);
    
    
	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
	
    
    
}
void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){
    
	Mat temp;
	threshold.copyTo(temp);
	//esse dois vetores são nescessarios para a criação do findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
                
				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;
                
				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
                    
				}else objectFound = false;
                
                
			}
			//let user know you found an object
			if(objectFound ==true){
				putText(cameraFeed,"Ratreando Carro...",Point(0,50),2,1,Scalar(0,255,0),2);
				//draw object location on screen
				drawObject(x,y,cameraFeed);}
            
		}else putText(cameraFeed,"Muito Ruido, favor ajustar o filtro!",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}
int main(int argc, char* argv[])
{
    /*        CONFIGURAÇÃO SERIAL      */
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_usb;
    char buffer [33];

    /*
     * CONFIGURE USB PORT
     */
    configureOximeter(&stdio, &tio, &old_stdio);
    
    /*
     * OPENNING USB PORT TO I/O COMMUNICATION
     */
    
    openUSB(&tty_usb, &tio);
    /*
     * LEITURA E ESCRITA NA PORTA USB
     *
     */
    
    /*     FIM DA CONFIGURAÇÃO SERIAL */
    
    
	//some boolean variables for different functionality within this
	//program
    bool trackObjects = true;
    bool useMorphOps = true;
	//Matrix to store each frame of the webcam feed
	Mat cameraFeed;
	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	//x and y values for the location of the object
	int x=0, y=0;
	//create slider bars for HSV filtering
	createTrackbars();
	//video capture object to acquire webcam feed
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	capture.open(0);
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	while(1){
		//store image to matrix
		capture.read(cameraFeed);
		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
		//filter HSV image between values and store filtered image to
		//threshold matrix
		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
		//perform morphological operations on thresholded image to eliminate noise
		//and emphasize the filtered object(s)
		if(useMorphOps)
            morphOps(threshold);
		//pass in thresholded frame to our object tracking function
		//this function will return the x and y coordinates of the
		//filtered object
		if(trackObjects)
        {
			trackFilteredObject(x,y,threshold,cameraFeed);
            write(tty_usb, &y, 8); //escreve p na porta serial
            //read(tty_usb, &leitura, 4); //ler a porta serial

        }
        //exibir os frames
		imshow(windowName2,threshold);
		imshow(windowName,cameraFeed);
		imshow(windowName1,HSV);
		
        
		//delay de 30ms para a atualização da tela.
		//sem esse comando não aparece imagem!!!!
		waitKey(200);
	}
    
    
    
    
    
    
	return 0;
}

