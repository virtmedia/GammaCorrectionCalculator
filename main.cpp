#include <iostream>
#include <windows.h>
#include <string.h>
#include <math.h>

//using namespace std;

HWND hButton1; //Generate
HWND hLabel1; //Corection factor
HWND hLabel2; //number of elements in array
HWND hLabel3; //max output value from 0
HWND hLabel4; //Author: Aleksander Kaweczynski
HWND hLabel5; //E.VT0.PL

HWND hCheckBox1;


char onlyOneZero = 1;

HWND hEdit1; //Corection factor
HWND hEdit2; //number of elements in array
HWND hEdit3; //max output value from 0

HWND hText1; //generated code

std::string intToStr(int n)
{
     std::string tmp, ret;
     if(n < 0) {
      ret = "-";
      n = -n;
     }
     do {
      tmp += n % 10 + 48;
      n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
      ret += tmp[i];
     return ret;
}

void hButton1OnClick();

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_COMMAND: {
			if(wParam == 1){
				if(( HWND ) lParam == hButton1 )
					hButton1OnClick();
					//MessageBox(NULL, "Click","Button1",MB_ICONEXCLAMATION|MB_OK);
				
				
			}
			
			if(wParam == 2){
				if((HWND) lParam == hCheckBox1){
					BOOL checked = IsDlgButtonChecked(hwnd, 2);
			    	if (checked) {
			        	CheckDlgButton(hwnd, 2, BST_UNCHECKED);
			    		onlyOneZero = 0;
			    	} else {
			    		CheckDlgButton(hwnd, 2, BST_CHECKED);
			    		onlyOneZero = 1;
			   		}
				}
			}
			
			
					
			
			break;
		}
		/*
		case WM_SYSCOMMAND: {
			if(wParam == SC_CLOSE){
				PostQuitMessage(0);	
			}
			break;
		}
		*/
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Gamma correction calculator",WS_VISIBLE|WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		450, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	
	hLabel1 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 15, 10, 150, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( hLabel1, "Correction factor:" );
	hLabel2 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 175, 10, 150, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( hLabel2, "Number of elements:" );
	hLabel3 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 335, 10, 150, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( hLabel3, "Max output value:" );
	hEdit1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 30, 150, 20, hwnd, NULL, hInstance, NULL );
	hEdit2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 170, 30, 150, 20, hwnd, NULL, hInstance, NULL );
	hEdit3 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 330, 30, 150, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( hEdit1, "2.5" );
	SetWindowText( hEdit2, "100" );
	SetWindowText( hEdit3, "255" );
	
	hCheckBox1 = CreateWindowEx( 0, "BUTTON", "Only first 0", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 490, 20, 150, 30, hwnd, (HMENU)2, hInstance, NULL );
	CheckDlgButton(hwnd, 2, BST_CHECKED);
	
	hText1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 10, 60, 610, 300, hwnd, NULL, hInstance, NULL );
	SetWindowText( hText1, "Here will be your code :)" );
	hButton1 = CreateWindow("BUTTON", "Generate!", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,245,370,150,20,hwnd,(HMENU)1,hInstance,NULL );
	
	hLabel4 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 15, 370, 200, 40, hwnd, NULL, hInstance, NULL );
	SetWindowText( hLabel4, "Author: \r\nAleksander Kaweczynski" );
	hLabel5 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 450, 370, 150, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( hLabel5, "E.VT0.pl 2016 v0.1" );
	
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}


void hButton1OnClick()
{
	double factor;
	DWORD dlugosc = GetWindowTextLength( hEdit1 );
	LPSTR Bufor =( LPSTR ) GlobalAlloc( GPTR, dlugosc + 1 );
	GetWindowText( hEdit1, Bufor, dlugosc + 1 );
	factor = atof(Bufor);
	GlobalFree( Bufor );
	
	int elements;
	dlugosc = GetWindowTextLength( hEdit2 );
	Bufor =( LPSTR ) GlobalAlloc( GPTR, dlugosc + 1 );
	GetWindowText( hEdit2, Bufor, dlugosc + 1 );
	elements = atoi(Bufor);
	GlobalFree( Bufor );
	
	int maxvalue;
	dlugosc = GetWindowTextLength( hEdit3 );
	Bufor =( LPSTR ) GlobalAlloc( GPTR, dlugosc + 1 );
	GetWindowText( hEdit3, Bufor, dlugosc + 1 );
	maxvalue = atoi(Bufor);
	GlobalFree( Bufor );
	
	std::string text1;
	
	if(maxvalue <= 0xFF)
		text1 = "const uint8_t gamma[";
	else if(maxvalue <= 0xFFFF)
		text1 = "const uint16_t gamma[";
	else
		text1 = "const uint32_t gamma[";
	
	text1 += intToStr(elements);
	text1 += "] = {";
	int val=0;
	for(int i=1;i<=elements;++i)
	{
		val = round(maxvalue*( pow((((double)maxvalue/(double)elements*((double)i))/(double)maxvalue) , factor)  ));
		
		if((val == 0) && (onlyOneZero) && (i>1))
			val = 1;
		
		text1 += intToStr(val);
		if(i<elements)
			text1 += ",";
		text1 += " ";
	}
	
	
	text1 += "};\r\n/*\r\nExample usage in AVR C:\r\nOCR0A = gamma[2];\r\nOr, if you want save RAM, add to header:\r\n#include <avr/pgmspace.h>\r\nadd to array definition keyword PROGMEM before equals sign\r\nUsage:\r\nOCR0A = pgm_read_byte(&gamma[2]);\r\n*/";
	LPCSTR abc = text1.c_str();
	
	SetWindowText( hText1, abc );
	
}
