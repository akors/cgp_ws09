//==================================================================================
//	Class for a graphical interface for X11 Windows
//	Haye Hinrichsen, 1997-2006, free software (GNU)
//==================================================================================

/***********************************************************************************
	Usage: See documentation instructions.odt.
	Needs: package xorg-x11
	SaveImage needs the command xgrabsc
	CreateMovie needs jpeg2yuv and yuvscaler
***********************************************************************************/

#ifndef XWINDOWS
#define XWINDOWS

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define Error(c) std::cout << "Error: " << (c) << std::endl;

class XWindow
{
public:
// CONSTRUCTOR
    XWindow (int xx0, int yy0);

// WINDOW CONTROL
	void Open (const int xsize=600, const int ysize=400, const char* title = "");
	void Clear (void) { XClearWindow(display, window); };
	int  GetX (void) { return xsize; }
	int  GetY (void) { return ysize; }
	inline bool IsOpen (void) { return (window!=0); }
	int  GetWindowID (void) { return (int)window; }
	void Close(void);

// DRAWING
	void DrawPoint (const int x, const int y);
	void DrawPoint (const int x, const int y, bool visible);
	void DrawLine (const int x1, const int y1, const int x2, const int y2);
	void Flush (void) { XFlush(display); }

// WRITING TEXT
	void SetFontsize (const int index=1);
	void DrawText (const int x, const int y, const char* c);

// COLORS
	void SetColor (const double c); // continuous color scale 0<c<1
	void SetColor (const int k);
	void Red (void) 	{ XSetForeground(display, gc, 0xFF0000L); }
	void Yellow (void) 	{ XSetForeground(display, gc, 0xFFFF00L); }
	void Green (void)	{ XSetForeground(display, gc, 0x00FF00L); }
	void Blue (void)	{ XSetForeground(display, gc, 0x0000FFL); }
	void Violet (void)	{ XSetForeground(display, gc, 0xFF00FFL); }
	void Black (void) 	{ XSetForeground(display, gc, 0x000000L); }
	void Grey (void)	{ XSetForeground(display, gc, 0x7F7F7FL); }
	void LightGrey (void)	{ XSetForeground(display, gc, 0xAFAFAFL); }
	void White (void)	{ XSetForeground(display, gc, 0xFFFFFFL); }

// HANDLE KEYBOARD
	bool KeyIsPressed (void);
	char GetCharacter (void) { KeyPressed=false; return (PressedKey); }
	char WaitForKeypress (void) { XFlush(display); while (! KeyIsPressed());
	                              return GetCharacter(); }
	void Wait (void) { while (! KeyIsPressed()); GetCharacter(); }

// GENERATE  PICTURES
	bool WriteImage (const char* filename);

// GENERATE  MOVIES
	void ClearMovie (void);
	void AddFrame (void);
	void CreateMovie (const char* filename, const int frames=20,
	                  const int mpeglayer=1);

private:
	static const int distance = 40;		// shift distance
	static int xcorner, ycorner;		// upper left edge
	Display *display;			// Display handler
	Window window;				// Window handler
	GC gc,gc2;				// device context
	XEvent event;				// event flag
	KeySym key;				// key
	char PressedKey, KeyPressed;		// keypress flag
	XSizeHints hint;			// hint default coordinates
	int screen, xsize, ysize;		// window sizes
	unsigned long foreground, background;	// foreground and background colors
	int n;					// number of movie frames dropped
	static const char* tmp;			// path of movie frames
	Font font[5];				// Array of fonts (0..4)
	int actual_font;			// actual font size

};

const char* XWindow::tmp = "/tmp/X11MovieFrames";	// temporary path for movie frames
//int XWindow::xcorner = 130;			// default location of corner
//int XWindow::ycorner = 100;
int XWindow::xcorner = 1000;			// default location of corner
int XWindow::ycorner = 0;

//----------------------------------------------------------------------------------
//	Constructor
//----------------------------------------------------------------------------------

XWindow::XWindow (int xx0, int yy0)
{
xcorner = xx0;
ycorner = yy0;
PressedKey=0; KeyPressed=false; n=window=0;
hint.x = xcorner; hint.y = ycorner;
xcorner += distance; ycorner += distance;
}


//----------------------------------------------------------------------------------
//	Open the window
//----------------------------------------------------------------------------------

void XWindow::Open (const int xsize, const int ysize, const char* title)
{
this->xsize = xsize; this->ysize = ysize;
display = XOpenDisplay("");
if (not display) Error("XWindow::Open: Failed to open display.");
screen = DefaultScreen(display);
background = WhitePixel(display, screen);
foreground = BlackPixel(display, screen);
hint.width = xsize; hint.height = ysize;
hint.flags = PPosition | PSize;
window = XCreateSimpleWindow(display, DefaultRootWindow(display), hint.x, hint.y,
 	 hint.width, hint.height, 5, foreground, background);
XSetStandardProperties(display, window, title, title, None, 0, 0, &hint);
gc=XCreateGC(display, window, 0, 0);	// gc for black
gc2=XCreateGC(display, window, 0, 0);	// gc for white
XSetBackground(display, gc, background);
XSetForeground(display, gc, foreground);
XSetBackground(display, gc2, foreground);
XSetForeground(display, gc2, background);
XSelectInput(display, window, ButtonPressMask | KeyPressMask | ExposureMask);
XMapRaised(display, window);
XNextEvent(display, &event);
font[0] = XLoadFont(display,"-adobe-courier-medium-r-normal--10-*-iso8859-1");
font[1] = XLoadFont(display,"-adobe-courier-medium-r-normal--12-*-iso8859-1");
font[2] = XLoadFont(display,"-adobe-courier-bold-r-normal--17-*-iso8859-1");
font[3] = XLoadFont(display,"-adobe-courier-bold-r-normal--24-*-iso8859-1");
font[4] = XLoadFont(display,"-adobe-courier-bold-r-normal--34-*-iso8859-1");
SetFontsize();
}


//----------------------------------------------------------------------------------
//	Draw a point
//----------------------------------------------------------------------------------

void XWindow::DrawPoint (const int x, const int y)
{XDrawPoint(display, window, gc, x, y);}

void XWindow::DrawPoint (const int x, const int y, const bool visible)
{if (visible) XDrawPoint(display, window, gc, x, y);
 else XDrawPoint(display, window, gc2, x, y);}


//----------------------------------------------------------------------------------
//	Draw a line
//----------------------------------------------------------------------------------

void XWindow::DrawLine (const int x1, const int y1, const int x2, const int y2)
{XDrawLine(display, window, gc, x1, y1, x2, y2);}


//----------------------------------------------------------------------------------
//	Select one out of 5 possible font sizes
//----------------------------------------------------------------------------------

void XWindow::SetFontsize (const int size)
{
if (size<0 or size>4) Error ("XWindow::SetFontsize: size index must be in 0...4");
XSetFont (display, gc, font[size]);
}


//----------------------------------------------------------------------------------
//	Draw string on the screen
//----------------------------------------------------------------------------------

void XWindow::DrawText (const int x, const int y, const char* s)
{
const int width = 11;
const int height = 20;
int n = strlen(s);
if (s>0)
	{
	White();
	XFillRectangle (display, window, gc, x, y-3*height/4, width*n, height);
	Black();
	//XDrawRectangle (display, window, gc, x, y-3*height/4, width*n, height);
	XDrawString (display, window, gc, x, y, s, n);
	}
}


//----------------------------------------------------------------------------------
//	Set a continuous and periodic color scale
//----------------------------------------------------------------------------------

void XWindow::SetColor(const double c)
{
double c1=c-floor(c);
double c2=c1+1.0/3-floor(c1+1.0/3);
double c3=c2+1.0/3-floor(c2+1.0/3);
int r = 255-(c1<0.5 ? (int)(512*c1) : 511-(int)(512*c1));
int g = 255-(c2<0.5 ? (int)(512*c2) : 511-(int)(512*c2));
int b = 255-(c3<0.5 ? (int)(512*c3) : 511-(int)(512*c3));
XSetForeground(display, gc, r<<16 | g<<8 | b);
}

// On some computers this version is needed:

/*void XWindow::SetColor(const double c)
{
double c1=c-floor(c);
double c2=c1+1.0/3; c2-=floor(c2);
double c3=c2+1.0/3; c3-=floor(c3);
int r = 31-(c1<0.5 ? (int)(64*c1) : 63-(int)(64*c1));
int g = 31-(c2<0.5 ? (int)(64*c2) : 63-(int)(64*c2));
int b = 31-(c3<0.5 ? (int)(64*c3) : 63-(int)(64*c3));
XSetForeground(display, gc, r<<11 | g<<6 | b);
}*/


//----------------------------------------------------------------------------------
//	Set discrete colors
//----------------------------------------------------------------------------------

void XWindow::SetColor (const int k)
{
const int n=6;
switch (k%n)
	{
	case 0:	Black();  break;
	case 1: Red();    break;
	case 2: Green();  break;
	case 3: Blue();	  break;
	case 4: Yellow(); break;
	case 5: Violet(); break;
	default: std::cout << "XWindow::SetColor (int k): internal error." << std::endl;
	}
}


//----------------------------------------------------------------------------------
//	Save image in various graphics formats
//----------------------------------------------------------------------------------

bool XWindow::WriteImage (const char* filename)
{
char commandline[200];
XFlush(display);
if (strlen(filename)<5)
	{
	Error("XWindow::SaveImage: Invalid file name");
	return false;
	}
const char* extension = filename + strlen(filename) - 4;
if (strcasecmp(extension,".eps")==0)
	{
	std::cout << " eps identified." << std::endl;
	sprintf(commandline,"xgrabsc -nobell -id %d -eps -cps -o %s",
                GetWindowID(),filename);
	system(commandline);
	}
else if (strcasecmp(extension,".ppm")==0)
	{
	std::cout << " ppm identified." << std::endl;
	sprintf(commandline,"xgrabsc -nobell -id %d -ppm -o %s",GetWindowID(),filename);
	system(commandline);
	}
else if (strcasecmp(extension,".jpg")==0 or strcasecmp(extension,"jpeg")==0)
	{
	std::cout << " jpg identified." << std::endl;
	sprintf(commandline,"xgrabsc -nobell -id %d -ppm | ppmtojpeg > %s",
                GetWindowID(),filename);
	system(commandline);
	}
else
	{
	std::cerr << "XWindow::SaveImage: Unknown extension " << extension << std::endl;
	return false;
	}

        std::cout << " File written ." << std::endl;

return true;
}


//----------------------------------------------------------------------------------
//	Determine whether key has been pressed
//----------------------------------------------------------------------------------

bool XWindow::KeyIsPressed (void)
{
if (KeyPressed) return true;
if (! XCheckTypedEvent(display,KeyPress,&event)) return false;
int i; char text[10];
i=XLookupString((XKeyEvent *) &event, text, 10, &key, 0);
if (i!=1) return false;;
PressedKey=text[0]; KeyPressed=true;
return true;
}


//----------------------------------------------------------------------------------
//	Movie functions: Clear frame buffer
//----------------------------------------------------------------------------------

void XWindow::ClearMovie (void)
{
char commandline[200];
n=0;
sprintf (commandline,"rm -r -f %s",tmp);		// remove temporary directory
system(commandline);
}


//----------------------------------------------------------------------------------
//	Movie functions: Add a single frame
//----------------------------------------------------------------------------------

void XWindow::AddFrame (void)
{
char commandline[200];
if (n==0)
	{
	ClearMovie();
	sprintf (commandline,"mkdir %s",tmp);		// create a temporary directory
	system(commandline);
	}
sprintf (commandline,"%s/image%08d.jpg",tmp,n);		// save one frame as a jpeg there
std::cout << "write image " << commandline << std::endl;
WriteImage(commandline);
n++;
}


//----------------------------------------------------------------------------------
//	Movie function: Create a movie in DVD-compatible format
//----------------------------------------------------------------------------------

void XWindow::CreateMovie (const char* filename, const int frames,
                           const int mpeglayer)
{
char commandline[200];	// call Linux commands to assemble movies in DVD size
if (mpeglayer==1)
	{
	sprintf (commandline,"jpeg2yuv -f %d -I p -j %s/image%%08d.jpg | yuvscaler -O DVD | mpeg2enc -o %s",frames,tmp,filename);
	system(commandline);
	}
else if (mpeglayer==2)
	{
	sprintf (commandline,"jpeg2yuv -f %d -I p -j %s/image%%08d.jpg | yuvscaler -O DVD | mpeg2enc -f 3 -b 3000 -o %s",frames,tmp,filename);
	system(commandline);
	}
else Error ("XWindow::CreateMovie: So far only MPEG layer 1 and 2 implemented");
std::cout << commandline << std::endl;
}


//----------------------------------------------------------------------------------
//	Close the window
//----------------------------------------------------------------------------------

void XWindow::Close()
{
XFreeGC(display, gc);
XDestroyWindow(display, window);
XCloseDisplay(display);
window = 0;
if (xcorner>0) xcorner -= distance;
if (ycorner>0) ycorner += distance;
}




#endif

