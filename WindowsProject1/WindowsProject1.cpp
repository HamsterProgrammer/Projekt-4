#include "framework.h"
#include "WindowsProject1.h"
#include <vector>
#include <cstdio>

#define MAX_LOADSTRING 100

bool bDrawTriangle = false;
bool bDrawCircle = false;
bool bDrawSquare = false;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND hwndButton;
int x = 20;
int y = 100;
int ground = 250;
bool picked_up = 0;
int pickme = 0;
char shape;
bool block = 0;

//initialization of figures, add a funktion that will give you an additional figures
std::vector<int> boxes_x = { 1000, 800 };        //200, 400};
std::vector<int> boxes_y = { 200, 200 }; //200};
std::vector<int> boxes_masa = { 99, 99 };

std::vector<int> triangles_x = { 200, 300, 400 };
std::vector<int> triangles_y = { 200 , 200, 200 };
std::vector<int> triangles_masa = { 99 ,98, 97 };

std::vector<int> circles_x = { 500, 600, 700 };//, 700 };
std::vector<int> circles_y = { 200, 200, 200 };//, 200 };
std::vector<int> circles_masa = { 90, 90, 95 };


/*zmienić żeby nie było triangle_x itd wszystko zapisuje się w boxes i jak chce się stworzyć trójkąt to po prostu się odp funkcja wczyta
żeby sprawdzało czy jest trójkątem, kwadratem ... to bd funkcja sprawdzająca czy jest którąś z tych 3 to oddaje wartość true i może sprawdzać czy x znajduje się
w tych figurach aby je podnieśći mamy pierwsze 3 gotowe później dodać sprawdzanie masy(może pokazywanie jej?) i mamy 4 to śmieszne budowanie to idk */

void MyOnPaint(HDC hdc, int x, int y)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 0, 0, 255));
    graphics.DrawLine(&pen, x, 10, x, y);      // rysuj xyz tu bd że współrzędne zależa od tego jak przytrzymasz czy inny chuj i jeśli 
    // coś się zetknie czycos to sie klei do sb albo jak sie kliknie współ. sie zapisuja itp itd
}

// zrb wierzchołki ile wierzchołków ma figura i gdzie
std::vector<int> wierzcholki{ {4} };  // przy sprawdzaniu kwadratu i kółka sprawdź czy są równe       

void drawBox(HDC hdc, std::vector<int> boxes_x, std::vector<int> boxes_y)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    for (int g = 0; g < boxes_x.size(); g++)
        graphics.DrawRectangle(&pen, boxes_x[g], boxes_y[g], 50, 50);

}

void addNewTriangle(std::vector<int> triangles_x, std::vector<int> triangles_y, std::vector<int> triangles_masa, int mass=96, int x=120, int y=200) {
    triangles_x.push_back(x);
    triangles_y.push_back(y);
    triangles_masa.push_back(mass);
}
void addNewSquare(std::vector<int> boxes_x, std::vector<int> boxes_y, std::vector<int> boxes_masa, int mass = 96, int x = 150, int y = 200) {
    boxes_x.push_back(x);
    boxes_y.push_back(y);
    boxes_masa.push_back(mass);
}
void addNewCircle(std::vector<int> circles_x, std::vector<int>circles_y, std::vector<int> circles_masa, int mass = 96, int x = 180, int y = 200) {
    circles_x.push_back(x);
    circles_y.push_back(y);
    circles_masa.push_back(mass);
}

void drawTriangle(HDC hdc, std::vector<int> triangles_x, std::vector<int> triangles_y)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    for (int g = 0; g < triangles_x.size(); g++)
    {
        graphics.DrawLine(&pen, triangles_x[g], triangles_y[g], triangles_x[g] - 25, triangles_y[g] + 50);
        graphics.DrawLine(&pen, triangles_x[g], triangles_y[g], triangles_x[g] + 25, triangles_y[g] + 50);
        graphics.DrawLine(&pen, triangles_x[g] - 25, triangles_y[g] + 50, triangles_x[g] + 25, triangles_y[g] + 50);
    }
}

void drawCircle(HDC hdc, std::vector<int> circles_x, std::vector<int> circles_y)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    for (int g = 0; g < circles_x.size(); g++)
        graphics.DrawArc(&pen, circles_x[g], circles_y[g], 50, 50, 0, 360);
}


void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int x, int y)
{
    if (drawArea == NULL)
        InvalidateRect(hWnd, NULL, TRUE); // repaint all
    else
        InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
    hdc = BeginPaint(hWnd, &ps);
    MyOnPaint(hdc, x, y);
    drawBox(hdc, boxes_x, boxes_y);
    drawTriangle(hdc, triangles_x, triangles_y);
    drawCircle(hdc, circles_x, circles_y);
    EndPaint(hWnd, &ps);
}

void make_tower_1(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int& x, int& y)
{
    boxes_x = { 100 };
    boxes_y = { 200 };
    triangles_x = { 200 };
    triangles_y = { 200 };
    circles_x = { 300 };
    circles_y = { 200 };

    while (x != boxes_x[0])
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != boxes_y[0])
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100)
    {
        y -= 5;
        boxes_y[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20)
    {
        x -= 5;
        boxes_x[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    boxes_y[0] = 200;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != triangles_x[0])
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != triangles_y[0])
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100)
    {
        y -= 5;
        triangles_y[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20 + 25)
    {
        x -= 5;
        triangles_x[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    triangles_y[0] = 150;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != circles_x[0])
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != circles_y[0])
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100)
    {
        y -= 5;
        circles_y[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20)
    {
        x -= 5;
        circles_x[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    circles_y[0] = 100;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);
}

void make_tower_2(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int& x, int& y)
{
    while (x != circles_x[0])
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != circles_y[0])
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100)
    {
        y -= 5;
        circles_y[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20)
    {
        x -= 5;
        circles_x[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    circles_y[0] = 200;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != boxes_x[0])
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != boxes_y[0])
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100)
    {
        y -= 5;
        boxes_y[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20)
    {
        x -= 5;
        boxes_x[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    boxes_y[0] = 150;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != triangles_x[0])
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != triangles_y[0])
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100)
    {
        y -= 5;
        triangles_y[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20 + 25)
    {
        x -= 5;
        triangles_x[0] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    triangles_y[0] = 100;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    hwndButton = CreateWindow(TEXT("Add box"),                      // The class name required is button
        TEXT("Move"),                  // the caption of the button
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
        800, 60,                                  // the left and top co-ordinates
        80, 50,                              // width and height
        hWnd,                                 // parent window handle
        (HMENU)ID_BUTTON,                   // the ID of your button
        hInstance,                            // the instance of your application
        NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_BUTTON:
            boxes_x.push_back(200);
            boxes_y.push_back(200);
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_CIRCLE:
            bDrawCircle != bDrawCircle;
           // addNewCircle(circles_x, circles_y, circles_masa);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_TRIANGLE:
            bDrawTriangle != bDrawTriangle;
            //addNewTriangle(triangles_x, triangles_y, triangles_masa);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_SQUARE:
            bDrawSquare != bDrawSquare;
            //addNewSquare(boxes_x, boxes_y, boxes_masa);
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
   
    // do zrb dodać block'i góra dół i trójkąt do tych równań może hitboxy polepszyć
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            block = 0;
            if (picked_up == 1 and shape == 's')
            {
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (boxes_x[pickme] == boxes_x[g] - 50 and boxes_y[pickme] < boxes_y[g] + 50 and boxes_y[pickme] > boxes_y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (boxes_x[pickme] - 50 == circles_x[g] and boxes_y[pickme] < circles_y[g] + 50 and boxes_y[pickme] > circles_y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    int szer = (boxes_y[pickme] + 50 - triangles_y[g]) / 2;
                    if (boxes_x[pickme] + 2 <= triangles_x[g] + szer and boxes_y[pickme] + 50 > triangles_y[g] and boxes_y[pickme] < triangles_y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x - 5;
                    boxes_x[pickme] -= 5;
                }
            }
            if (picked_up == 1 and shape == 'c')
            {
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (circles_x[pickme] - 50 == circles_x[g] and circles_y[pickme] > circles_y[g] + 50 and circles_y[pickme] < circles_y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (circles_x[pickme] - 50 == boxes_x[g] and circles_y[pickme] - 50 > boxes_y[g] and circles_y[pickme] < boxes_y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    int szer = (circles_y[pickme] + 50 - triangles_y[g]) / 2;
                    if (circles_x[pickme] <= triangles_x[g] + szer and circles_y[pickme] + 50 > triangles_y[g] and circles_y[pickme] < triangles_y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x - 5;
                    circles_x[pickme] -= 5;
                }
            }
            if (picked_up == 1 and shape == 't')
            {
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (triangles_x[pickme] - 25 == circles_x[g] + 50 and triangles_y[pickme] + 50 >= circles_y[g] and triangles_y[pickme] + 50 <= circles_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (triangles_x[pickme] - 25 == boxes_x[g] + 50 and triangles_y[pickme] + 50 >= boxes_y[g] and triangles_y[pickme] + 50 <= boxes_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    if (pickme != g)
                    {
                        int szer = (triangles_y[pickme] - triangles_y[g]) / 2;
                        if (triangles_x[pickme] - 25 - 5 <= triangles_x[g] + szer and triangles_x[pickme] - 25 - 5 > triangles_x[g] + 25 and triangles_y[pickme] + 50 > triangles_y[g] and triangles_y[pickme] < triangles_y[g] + 50)
                            block = 1;
                    }
                }
                if (block == 0)
                {
                    x = x - 5;
                    triangles_x[pickme] -= 5;
                }
            }
            if (picked_up == 0)
                x = x - 5;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_RIGHT:
            block = 0;
            if (picked_up == 1 and shape == 's')
            {
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (boxes_x[pickme] + 50 == boxes_x[g] and boxes_y[pickme] > boxes_y[g] - 50 and boxes_y[pickme] < boxes_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (boxes_x[pickme] + 50 == circles_x[g] and boxes_y[pickme] > circles_y[g] - 50 and boxes_y[pickme] < circles_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    int szer = (boxes_y[pickme] + 50 - triangles_y[g]) / 2;
                    if (boxes_x[pickme] + 50 <= triangles_x[g] - szer and boxes_y[pickme] + 50 > triangles_y[g] and boxes_y[pickme] < triangles_y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x + 5;
                    boxes_x[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 'c')
            {
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (circles_x[pickme] + 50 == circles_x[g] and circles_y[pickme] > circles_y[g] - 50 and circles_y[pickme] < circles_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (circles_x[pickme] + 50 == boxes_x[g] and circles_y[pickme] > boxes_y[g] - 50 and circles_y[pickme] < boxes_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    int szer = (circles_y[pickme] + 50 - triangles_y[g]) / 2;
                    if (circles_x[pickme] + 50 >= triangles_x[g] - szer and circles_x[pickme] + 50 <= triangles_x[g] + szer and circles_y[pickme] + 50 > triangles_y[g] and circles_y[pickme] < triangles_y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x + 5;
                    circles_x[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 't')
            {
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (triangles_x[pickme] + 25 == circles_x[g] and triangles_y[pickme] + 50 >= circles_y[g] and triangles_y[pickme] + 50 <= circles_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (triangles_x[pickme] + 25 == boxes_x[g] and triangles_y[pickme] + 50 >= boxes_y[g] and triangles_y[pickme] + 50 <= boxes_y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    if (g != pickme)
                    {
                        int szer;
                        if (triangles_y[pickme] >= triangles_y[g])
                        {
                            szer = (triangles_y[pickme] + 50 - triangles_y[g]) / 2;
                            if (triangles_x[pickme] + szer >= triangles_x[g] - 25 and triangles_y[pickme] < triangles_y[g] + 50)
                                block = 1;
                        }
                        if (triangles_y[pickme] < triangles_y[g])
                        {
                            szer = (triangles_y[g] + 50 - triangles_y[pickme]) / 2;
                            if (triangles_x[pickme] + 25 + 5 >= triangles_x[g] - szer and triangles_y[pickme] + 50 > triangles_y[g])
                                block = 1;
                        }
                    }
                }
                if (block == 0)
                {
                    x = x + 5;
                    triangles_x[pickme] += 5;
                }
            }
            if (picked_up == 0)
                x = x + 5;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_UP:
            if (y > 15)
                y = y - 5;
            if (picked_up == 1 and shape == 's')
                boxes_y[pickme] -= 5;
            if (picked_up == 1 and shape == 'c')
                circles_y[pickme] -= 5;
            if (picked_up == 1 and shape == 't')
                triangles_y[pickme] -= 5;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_DOWN:// nie ma hitboxa dokończonego
            block = 0;
            if (picked_up == 1 and shape == 's')
            {
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (boxes_y[pickme] == boxes_y[g] - 50 and boxes_x[pickme] > boxes_x[g] - 50 and boxes_x[pickme] < boxes_x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (boxes_y[pickme] == circles_y[g] - 50 and boxes_x[pickme] > circles_x[g] - 50 and boxes_x[pickme] < circles_x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    if (boxes_x[pickme] + 50 > triangles_x[g] - 25 and boxes_x[pickme] + 50 < triangles_x[g])
                    {
                        int wys = 2 * (-boxes_x[pickme] - 50 + triangles_x[g]);
                        if (boxes_y[pickme] + 50 >= triangles_y[g] + wys)
                            block = 1;
                    }
                    if (boxes_x[pickme] > triangles_x[g] and boxes_x[pickme] < triangles_x[g] + 25)
                    {
                        int wys = 2 * (boxes_x[pickme] - triangles_x[g]);
                        if (boxes_y[pickme] + 50 >= triangles_y[g] + wys)
                            block = 1;
                    }
                    if (boxes_x[pickme] + 50 > triangles_y[g] and boxes_x[pickme] < triangles_x[g] and boxes_y[pickme] + 50 == triangles_y[g])
                        block = 1;

                }
                if (block == 0)
                {
                    y = y + 5;
                    boxes_y[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 'c')
            {
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (circles_y[pickme] == boxes_y[g] - 50 and circles_x[pickme] > boxes_x[g] - 50 and circles_x[pickme] < boxes_x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (circles_y[pickme] == circles_y[g] - 50 and circles_x[pickme] > circles_x[g] - 50 and circles_x[pickme] < circles_x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    if (circles_x[pickme] + 50 > triangles_x[g] - 25 and circles_x[pickme] + 50 < triangles_x[g])
                    {
                        int wys = 2 * (-circles_x[pickme] - 50 + triangles_x[g]);
                        if (circles_y[pickme] + 50 >= triangles_y[g] + wys)
                            block = 1;
                    }
                    if (circles_x[pickme] > triangles_x[g] and circles_x[pickme] < triangles_x[g] + 25)
                    {
                        int wys = 2 * (circles_x[pickme] - triangles_x[g]);
                        if (circles_y[pickme] + 50 >= triangles_y[g] + wys)
                            block = 1;
                    }
                    if (circles_x[pickme] + 50 > triangles_y[g] and circles_x[pickme] < triangles_x[g] and circles_y[pickme] + 50 == triangles_y[g])
                        block = 1;

                }
                if (block == 0)
                {
                    y = y + 5;
                    circles_y[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 't')
            {
                for (int g = 0; g < boxes_x.size(); g++)
                {
                    if (triangles_y[pickme] == boxes_y[g] - 50 and triangles_x[pickme] > boxes_x[g] - 50 and triangles_x[pickme] < boxes_x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles_x.size(); g++)
                {
                    if (triangles_y[pickme] == circles_y[g] - 50 and triangles_x[pickme] > circles_x[g] - 50 and triangles_x[pickme] < circles_x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles_x.size(); g++)
                {
                    if (triangles_x[pickme] + 25 > triangles_x[g] - 25 and triangles_x[pickme] + 25 < triangles_x[g])
                    {
                        int wys = 2 * (-triangles_x[pickme] - 25 + triangles_x[g]);
                        if (triangles_y[pickme] + 50 >= triangles_y[g] + wys)
                            block = 1;
                    }
                    if (triangles_x[pickme] - 25 > triangles_x[g] and triangles_x[pickme] - 25 < triangles_x[g] + 25)
                    {
                        int wys = 2 * (triangles_x[pickme] - 25 - triangles_x[g]);
                        if (triangles_y[pickme] + 50 >= triangles_y[g] + wys)
                            block = 1;
                    }
                    if (triangles_x[pickme] + 25 > triangles_y[g] and triangles_x[pickme] - 25 < triangles_x[g] and triangles_y[pickme] + 50 == triangles_y[g])
                        block = 1;

                    if (block == 0)
                    {
                        y = y + 5;
                        triangles_y[pickme] += 5;
                    }
                }
            }
            if (picked_up == 0)
                y = y + 5;

            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_END:
            boxes_x.push_back(200);
            boxes_y.push_back(200);
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;
        case VK_DELETE:
            make_tower_2(hWnd, hdc, ps, NULL, x, y);
        case 0x0D:
            //kółka 
            for (int g = 0; g < circles_x.size(); g++)
            {
                if (y > circles_y[g] and y < circles_y[g] + 50)
                {
                    if (x >= circles_x[g] and x <= circles_x[g] + 50)
                    {
                        if (picked_up == 0 and circles_masa[g] < 100)
                        {
                            pickme = g;
                            picked_up = 1;
                            shape = 'c';
                        }
                        else if (picked_up == 1)
                        {
                            picked_up = 0;
                            bool action = 0;
                            bool tower = 0;
                            int hight = ground;
                            bool diff = 0;

                            for (int h = 0; h < circles_y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (circles_y[pickme] != circles_y[h] and circles_x[pickme] - 50 <= circles_x[h] and circles_x[pickme] + 50 >= circles_x[h])
                                    {
                                        if (circles_y[h] == ground - 150)
                                        {
                                            tower = 1;
                                        }
                                        if (hight > circles_y[h])
                                            hight = circles_y[h];
                                    }
                                }
                            }
                            for (int h = 0; h < circles_y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (circles_y[g] != circles_y[h] and circles_x[g] - 50 <= circles_x[h] and circles_x[g] + 50 >= circles_x[h])
                                    {
                                        if (tower == 0 and diff == 0)
                                        {
                                            circles_y[g] = hight - 50;
                                            action = 1;
                                        }
                                        if (tower == 1 or diff == 1)
                                        {
                                            picked_up = 1;
                                            action = 1;
                                        }

                                    }
                                }
                            }
                            //kwadraty
                            for (int h = 0; h < boxes_y.size(); h++)
                            {

                                if (circles_x[g] + 50 >= boxes_x[h] and circles_x[g] <= boxes_x[h] + 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            //trójkąty
                            for (int h = 0; h < triangles_y.size(); h++)
                            {

                                if (circles_x[g] <= triangles_x[h] and circles_x[g] >= triangles_x[h] - 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            if (action == 0)
                                circles_y[g] = ground - 50;
                            repaintWindow(hWnd, hdc, ps, NULL, x, y);
                        }
                    }
                }
            }
            // kwadraty
            for (int g = 0; g < boxes_x.size(); g++)
            {
                if (y > boxes_y[g] and y < boxes_y[g] + 50)
                {
                    if (x >= boxes_x[g] and x <= boxes_x[g] + 50)
                    {

                        if (picked_up == 0 and boxes_masa[g] < 100)
                        {
                            pickme = g;
                            picked_up = 1;
                            shape = 's';
                        }
                        else if (picked_up == 1)
                        {
                            picked_up = 0;
                            bool action = 0;
                            bool tower = 0;
                            int hight = ground;
                            bool diff = 0;
                            for (int h = 0; h < boxes_y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (boxes_y[g] != boxes_y[h] and boxes_x[g] - 50 <= boxes_x[h] and boxes_x[g] + 50 >= boxes_x[h])
                                    {
                                        if (boxes_y[h] == ground - 150)
                                        {
                                            tower = 1;
                                        }
                                        if (hight > boxes_y[h])
                                            hight = boxes_y[h];
                                    }
                                }
                            }
                            for (int h = 0; h < boxes_y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (boxes_y[g] != boxes_y[h] and boxes_x[g] - 50 <= boxes_x[h] and boxes_x[g] + 50 >= boxes_x[h])
                                    {
                                        if (tower == 0)
                                        {
                                            boxes_y[g] = hight - 50;
                                            action = 1;
                                        }
                                        if (tower == 1 or diff == 1)
                                        {
                                            picked_up = 1;
                                            action = 1;
                                        }
                                    }
                                }
                            }
                            //koło
                            for (int h = 0; h < circles_y.size(); h++)
                            {

                                if (boxes_x[g] <= circles_x[h] and boxes_x[g] >= circles_x[h] - 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            //trójkąt
                            for (int h = 0; h < triangles_y.size(); h++)
                            {

                                if (boxes_x[g] <= triangles_x[h] and boxes_x[g] >= triangles_x[h] - 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            if (action == 0)
                                boxes_y[g] = ground - 50;
                            repaintWindow(hWnd, hdc, ps, NULL, x, y);
                        }
                    }
                }
            }
            //trójkąty
            for (int g = 0; g < triangles_x.size(); g++)
            {
                if (y > triangles_y[g] and y < triangles_y[g] + 50)
                {
                    int szer = (y - triangles_y[g]) / 2;
                    if (x >= triangles_x[g] - szer and x <= triangles_x[g] + szer)
                    {

                        if (picked_up == 0 and triangles_masa[g] < 100)
                        {
                            pickme = g;
                            picked_up = 1;
                            shape = 't';
                        }
                        else if (picked_up == 1)
                        {
                            picked_up = 0;
                            bool action = 0;
                            bool tower = 0;
                            int hight = ground;
                            bool diff = 0;
                            //trójkąty
                            for (int h = 0; h < triangles_x.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (pickme != h and triangles_x[g] >= triangles_x[h] - 25 and triangles_x[g] <= triangles_x[h] + 25)
                                    {
                                        if (triangles_y[h] == ground - 150)
                                        {
                                            tower = 1;
                                        }
                                        if (hight > triangles_y[h])
                                            hight = triangles_y[h];
                                    }
                                }
                            }

                            for (int h = 0; h < triangles_y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (triangles_y[pickme] != triangles_y[h] and triangles_x[pickme] >= triangles_x[h] - 25 and triangles_x[pickme] <= triangles_x[h] + 25)
                                    {
                                        if (tower == 0)
                                        {
                                            triangles_y[g] = hight - 50;
                                            action = 1;
                                        }
                                        if (tower == 1)
                                        {
                                            picked_up = 1;
                                            action = 1;
                                        }
                                    }
                                }
                            }
                            //koło
                            for (int h = 0; h < circles_x.size(); h++)
                            {

                                if (triangles_x[pickme] - 25 <= circles_x[h] + 50 and triangles_x[pickme] + 25 >= circles_x[h])
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            //kwadrat
                            for (int h = 0; h < boxes_x.size(); h++)
                            {

                                if (triangles_x[pickme] - 25 <= boxes_x[h] + 50 and triangles_x[pickme] + 25 >= boxes_x[h])
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }

                            if (action == 0)
                                triangles_y[pickme] = ground - 50;
                            repaintWindow(hWnd, hdc, ps, NULL, x, y);
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        if (bDrawCircle) addNewCircle(circles_x, circles_y, circles_masa, 96, 40, 200);
        if (bDrawSquare) addNewSquare(boxes_x, boxes_y, boxes_masa, 96, 150, 200);
        if (bDrawTriangle) addNewTriangle(triangles_x, triangles_y, triangles_masa, 96, 180, 200);
        drawBox(hdc, boxes_x, boxes_y);
        drawCircle(hdc, circles_x, circles_y);
        drawTriangle(hdc, triangles_x, triangles_y);
        MyOnPaint(hdc, x, y);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
