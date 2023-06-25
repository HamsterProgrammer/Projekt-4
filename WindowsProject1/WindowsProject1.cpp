#include "WindowsProject1.h"

Shapes triangles;
Shapes boxes;
Shapes circles;

RoboHand hand;

void firstShapes() {
    triangles.addNewShape(100, 200, 97);
    triangles.addNewShape(550, 200, 99);
    triangles.addNewShape(300, 200, 92);
    circles.addNewShape(200, 200, 96);
    circles.addNewShape(500, 200, 95);
    circles.addNewShape(800, 200, 93);
    boxes.addNewShape(700, 200, 99);
    boxes.addNewShape(400, 200, 90);
    boxes.addNewShape(770, 200, 99);
    //initialization of roboHand (dzwig)
    hand.x = 20;
    hand.y = 50;
    hand.put = false;
}


/*zmienić żeby nie było triangle_x itd wszystko zapisuje się w boxes i jak chce się stworzyć trójkąt to po prostu się odp funkcja wczyta
żeby sprawdzało czy jest trójkątem, kwadratem ... to bd funkcja sprawdzająca czy jest którąś z tych 3 to oddaje wartość true i może sprawdzać czy x znajduje się
w tych figurach aby je podnieśći mamy pierwsze 3 gotowe później dodać sprawdzanie masy(może pokazywanie jej?) i mamy 4 to śmieszne budowanie to idk */

void MyOnPaint(HDC hdc, int x, int y)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 0, 0, 255));
    if (hand.canMove(x, y)) {
        hand.setX(x);
        hand.setY(y);
        graphics.DrawLine(&pen, hand.x, 10, hand.x, hand.y);      // rysuj xyz tu bd że współrzędne zależa od tego jak przytrzymasz czy inny chuj i jeśli 
        // coś się zetknie czycos to sie klei do sb albo jak sie kliknie współ. sie zapisuja itp itd
    }
}

// zrb wierzchołki ile wierzchołków ma figura i gdzie
std::vector<int> wierzcholki{ {4} };  // przy sprawdzaniu kwadratu i kółka sprawdź czy są równe       
/*
void drawBox(HDC hdc, Shapes boxes)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    for (int g = 0; g < boxes.x.size(); g++)
        graphics.DrawRectangle(&pen, boxes.x[g], boxes.y[g], 50, 50);

}*/
void drawBox(HDC hdc, Shapes boxes)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    Font font(L"Arial", 12);
    SolidBrush brush(Color(255, 0, 0, 0));

    for (int g = 0; g < boxes.x.size(); g++)
    {
        int centerX = boxes.x[g] + 25;  // Calculate the x-coordinate of the center of the box
        int centerY = boxes.y[g] + 25;  // Calculate the y-coordinate of the center of the box

        graphics.DrawRectangle(&pen, boxes.x[g], boxes.y[g], 50, 50);

        std::wstringstream wss;
        wss << boxes.masa[g];  // Convert integer to wide string using wstringstream

        std::wstring text = wss.str();  // Get the wide string from wstringstream

        graphics.DrawString(text.c_str(), -1, &font, PointF(centerX, centerY), &brush);
    }
}
/*
void drawTriangle(HDC hdc, Shapes triangles)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    for (int g = 0; g < triangles.x.size(); g++)
    {
        graphics.DrawLine(&pen, triangles.x[g], triangles.y[g], triangles.x[g] - 25, triangles.y[g] + 50);
        graphics.DrawLine(&pen, triangles.x[g], triangles.y[g], triangles.x[g] + 25, triangles.y[g] + 50);
        graphics.DrawLine(&pen, triangles.x[g] - 25, triangles.y[g] + 50, triangles.x[g] + 25, triangles.y[g] + 50);
    }
}

void drawCircle(HDC hdc, Shapes circles)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    for (int g = 0; g < circles.x.size(); g++)
        graphics.DrawArc(&pen, circles.x[g], circles.y[g], 50, 50, 0, 360);
}*/
void drawTriangle(HDC hdc, Shapes triangles)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    Font font(L"Arial", 12);
    SolidBrush brush(Color(255, 0, 0, 0));

    for (int g = 0; g < triangles.x.size(); g++)
    {
        graphics.DrawLine(&pen, triangles.x[g], triangles.y[g], triangles.x[g] - 25, triangles.y[g] + 50);
        graphics.DrawLine(&pen, triangles.x[g], triangles.y[g], triangles.x[g] + 25, triangles.y[g] + 50);
        graphics.DrawLine(&pen, triangles.x[g] - 25, triangles.y[g] + 50, triangles.x[g] + 25, triangles.y[g] + 50);

        int centerX = (triangles.x[g] + triangles.x[g] - 25 + triangles.x[g] + 25) / 3;
        int centerY = triangles.y[g] + 30; //(triangles.y[g] + triangles.y[g] + triangles.y[g] + 50 + triangles.y[g] + 50) / 3;

        std::wstringstream wss;
        wss << triangles.masa[g];  // Convert integer to wide string using wstringstream

        std::wstring text = wss.str();  // Get the wide string from wstringstream

        graphics.DrawString(text.c_str(), -1, &font, PointF(centerX, centerY), &brush);
    }
}

void drawCircle(HDC hdc, Shapes circles)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    Font font(L"Arial", 12);
    SolidBrush brush(Color(255, 0, 0, 0));

    for (int g = 0; g < circles.x.size(); g++)
    {
        graphics.DrawArc(&pen, circles.x[g], circles.y[g], 50, 50, 0, 360);

        int centerX = circles.x[g] + 25;
        int centerY = circles.y[g] + 25;

        std::wstringstream wss;
        wss << circles.masa[g];  // Convert integer to wide string using wstringstream

        std::wstring text = wss.str();  // Get the wide string from wstringstream

        graphics.DrawString(text.c_str(), -1, &font, PointF(centerX, centerY), &brush);
    }
}

void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int x, int y)
{
    if (drawArea == NULL)
        InvalidateRect(hWnd, NULL, TRUE); // repaint all
    else
        InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
    hdc = BeginPaint(hWnd, &ps);
    MyOnPaint(hdc, x, y);
    drawBox(hdc, boxes);
    drawTriangle(hdc, triangles);
    drawCircle(hdc, circles);
    EndPaint(hWnd, &ps);
}

void make_tower_1(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int& x, int& y)
{

    int searching_circle = 0;
    int searching_box = 0;
    int searching_triangle = 0;
    bool block = 0;
    for (int g = 0; g < circles.x.size(); g++)
    {
        block = 0;
        for (int h = 0; h < circles.x.size(); h++)
        {
            if (circles.y[g] - 50 == circles.y[h] and circles.x[g] + 50 > circles.x[h] and circles.x[g] < circles.x[h] + 50)
            {
                block = 1;
            }
        }
        if (block == 0)
            searching_circle = g;
    }
    for (int g = 0; g < triangles.x.size(); g++)
    {
        block = 0;
        for (int h = 0; h < triangles.x.size(); h++)
        {
            if (triangles.y[g] - 50 == triangles.y[h] and triangles.x[g] + 25 > triangles.x[h] - 25 and triangles.x[g] - 25 < triangles.x[h] + 25)
            {
                block = 1;
            }
        }
        if (block == 0)
            searching_triangle = g;
    }
    for (int g = 0; g < boxes.x.size(); g++)
    {
        for (int h = 0; h < boxes.y.size(); h++)
        {
            if (boxes.y[g] - 50 == boxes.y[h] and boxes.x[g] + 50 > boxes.x[h] and boxes.x[g] < boxes.x[h] + 50)
            {
                block = 1;
            }
        }
        if (block == 0)
            searching_box = g;
    }


    while (x != boxes.x[searching_box]+50 && hand.canMove(x + 5, y))
    {
            x += 5;
            repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != boxes.y[searching_box] && hand.canMove(x, y+5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y-5))
    {
        y -= 5;
        boxes.y[searching_box] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 75 && hand.canMove(x-5, y))
    {
        x -= 5;
        boxes.x[searching_box] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    boxes.y[searching_box] = 200;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != triangles.x[searching_triangle] && hand.canMove(x+5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != triangles.y[searching_triangle] && hand.canMove(x, y+5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y-5))
    {
        y -= 5;
        triangles.y[searching_triangle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 75 + 25 && hand.canMove(x-5, y))
    {
        x -= 5;
        triangles.x[searching_triangle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    triangles.y[searching_triangle] = 150;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != circles.x[searching_circle]+50 && hand.canMove(x+5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != circles.y[searching_circle] && hand.canMove(x, y+5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y-5))
    {
        y -= 5;
        circles.y[searching_circle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 75 && hand.canMove(x-5, y))
    {
        x -= 5;
        circles.x[searching_circle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    circles.y[searching_circle] = 100;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);
}

void make_tower_2(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int& x, int& y)
{
    //i'm wondering what's going on

    
    int searching_circle = 0;
    int searching_box = 0;
    int searching_triangle = 0;
    bool block = 0;
    for (int g = 0; g < circles.x.size(); g++)
    {
        block = 0;
        for (int h = 0; h < circles.x.size(); h++)
        {
            if (circles.y[g] - 50 == circles.y[h] and circles.x[g] + 50 > circles.x[h] and circles.x[g] < circles.x[h] + 50)
            {
                block = 1;
            }
        }
        if (block == 0)
            searching_circle = g;
    }
    for (int g = 0; g < triangles.x.size(); g++)
    {
        block = 0;
        for (int h = 0; h < triangles.x.size(); h++)
        {
            if (triangles.y[g] - 50 == triangles.y[h] and triangles.x[g] + 25 > triangles.x[h] - 25 and triangles.x[g] - 25 < triangles.x[h] + 25)
            {
                block = 1;
            }
        }
        if (block == 0)
            searching_triangle = g;
    }
    for (int g = 0; g < boxes.x.size(); g++)
    {
        for (int h = 0; h < boxes.y.size(); h++)
        {
            if (boxes.y[g] - 50 == boxes.y[h] and boxes.x[g] + 50 > boxes.x[h] and boxes.x[g] < boxes.x[h] + 50)
            {
                block = 1;
            }
        }
        if (block == 0)
            searching_box = g;
    }

    while (x != circles.x[searching_circle]+50 && hand.canMove(x+5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != circles.y[searching_circle] && hand.canMove(x, y+5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y-5))
    {
        y -= 5;
        circles.y[searching_circle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 75 && hand.canMove(x-5, y))
    {
        x -= 5;
        circles.x[searching_circle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    circles.y[searching_circle] = 200;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != boxes.x[searching_box]+50 && hand.canMove(x+5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != boxes.y[searching_box] && hand.canMove(x, y+5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y-5))
    {
        y -= 5;
        boxes.y[searching_box] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 75 && hand.canMove(x, y-5))
    {
        x -= 5;
        boxes.x[searching_box] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    boxes.y[searching_box] = 150;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    
    while (x != triangles.x[searching_triangle] && hand.canMove(x+5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != triangles.y[searching_triangle] && hand.canMove(x, y+5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y-5))
    {
        y -= 5;
        triangles.y[searching_triangle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 75 + 25 && hand.canMove(x-5, y))
    {
        x -= 5;
        triangles.x[searching_triangle] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    triangles.y[searching_triangle] = 100;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    firstShapes();
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
            boxes.x.push_back(200);
            boxes.y.push_back(200);
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
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_SQUARE:
            bDrawSquare != bDrawSquare;
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
            if (picked_up == 1 and shape == 's' && hand.canMove(x - 5, y))
            {
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (boxes.x[pickme] == boxes.x[g] - 50 and boxes.y[pickme] < boxes.y[g] + 50 and boxes.y[pickme] > boxes.y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (boxes.x[pickme] - 50 == circles.x[g] and boxes.y[pickme] < circles.y[g] + 50 and boxes.y[pickme] > circles.y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    int szer = (boxes.y[pickme] + 50 - triangles.y[g]) / 2;
                    if (boxes.x[pickme] + 2 <= triangles.x[g] + szer and boxes.y[pickme] + 50 > triangles.y[g] and boxes.y[pickme] < triangles.y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x - 5;
                    boxes.x[pickme] -= 5;
                }
            }
            if (picked_up == 1 and shape == 'c' && hand.canMove(x - 5, y))
            {
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (circles.x[pickme] - 50 == circles.x[g] and circles.y[pickme] > circles.y[g] + 50 and circles.y[pickme] < circles.y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (circles.x[pickme] - 50 == boxes.x[g] and circles.y[pickme] - 50 > boxes.y[g] and circles.y[pickme] < boxes.y[g] - 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    int szer = (circles.y[pickme] + 50 - triangles.y[g]) / 2;
                    if (circles.x[pickme] <= triangles.x[g] + szer and circles.y[pickme] + 50 > triangles.y[g] and circles.y[pickme] < triangles.y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x - 5;
                    circles.x[pickme] -= 5;
                }
            }
            if (picked_up == 1 and shape == 't' && hand.canMove(x - 5, y))
            {
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (triangles.x[pickme] - 25 == circles.x[g] + 50 and triangles.y[pickme] + 50 >= circles.y[g] and triangles.y[pickme] + 50 <= circles.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (triangles.x[pickme] - 25 == boxes.x[g] + 50 and triangles.y[pickme] + 50 >= boxes.y[g] and triangles.y[pickme] + 50 <= boxes.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    if (pickme != g)
                    {
                        int szer = (triangles.y[pickme] - triangles.y[g]) / 2;
                        if (triangles.x[pickme] - 25 - 5 <= triangles.x[g] + szer and triangles.x[pickme] - 25 - 5 > triangles.x[g] + 25 and triangles.y[pickme] + 50 > triangles.y[g] and triangles.y[pickme] < triangles.y[g] + 50)
                            block = 1;
                    }
                }
                if (block == 0 && hand.canMove(x - 5, y))
                {
                    x = x - 5;
                    triangles.x[pickme] -= 5;
                }
            }
            if (picked_up == 0) {
                if (hand.canMove(x - 5, y))
                    x = x - 5;
            }
            else x = x;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_RIGHT:
            block = 0;
            if (picked_up == 1 and shape == 's' && hand.canMove(x + 5, y))
            {
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (boxes.x[pickme] + 50 == boxes.x[g] and boxes.y[pickme] > boxes.y[g] - 50 and boxes.y[pickme] < boxes.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (boxes.x[pickme] + 50 == circles.x[g] and boxes.y[pickme] > circles.y[g] - 50 and boxes.y[pickme] < circles.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    int szer = (boxes.y[pickme] + 50 - triangles.y[g]) / 2;
                    if (boxes.x[pickme] + 50 <= triangles.x[g] - szer and boxes.y[pickme] + 50 > triangles.y[g] and boxes.y[pickme] < triangles.y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x + 5;
                    boxes.x[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 'c' && hand.canMove(x + 5, y))
            {
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (circles.x[pickme] + 50 == circles.x[g] and circles.y[pickme] > circles.y[g] - 50 and circles.y[pickme] < circles.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (circles.x[pickme] + 50 == boxes.x[g] and circles.y[pickme] > boxes.y[g] - 50 and circles.y[pickme] < boxes.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    int szer = (circles.y[pickme] + 50 - triangles.y[g]) / 2;
                    if (circles.x[pickme] + 50 >= triangles.x[g] - szer and circles.x[pickme] + 50 <= triangles.x[g] + szer and circles.y[pickme] + 50 > triangles.y[g] and circles.y[pickme] < triangles.y[g] + 50)
                        block = 1;
                }
                if (block == 0)
                {
                    x = x + 5;
                    circles.x[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 't' && hand.canMove(x + 5, y))
            {
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (triangles.x[pickme] + 25 == circles.x[g] and triangles.y[pickme] + 50 >= circles.y[g] and triangles.y[pickme] + 50 <= circles.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (triangles.x[pickme] + 25 == boxes.x[g] and triangles.y[pickme] + 50 >= boxes.y[g] and triangles.y[pickme] + 50 <= boxes.y[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    if (g != pickme)
                    {
                        int szer;
                        if (triangles.y[pickme] >= triangles.y[g])
                        {
                            szer = (triangles.y[pickme] + 50 - triangles.y[g]) / 2;
                            if (triangles.x[pickme] + szer >= triangles.x[g] - 25 and triangles.y[pickme] < triangles.y[g] + 50)
                                block = 1;
                        }
                        if (triangles.y[pickme] < triangles.y[g])
                        {
                            szer = (triangles.y[g] + 50 - triangles.y[pickme]) / 2;
                            if (triangles.x[pickme] + 25 + 5 >= triangles.x[g] - szer and triangles.y[pickme] + 50 > triangles.y[g])
                                block = 1;
                        }
                    }
                }
                if (block == 0)
                {
                    x = x + 5;
                    triangles.x[pickme] += 5;
                }
            }
            if (picked_up == 0 && hand.canMove(x + 5, y))
                x = x + 5;
            else x = x;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_UP:
            if (y > 15 && hand.canMove(x, y))
                y = y - 5;
            if (picked_up == 1 and shape == 's' && hand.canMove(x, y - 5))
                boxes.y[pickme] -= 5;
            if (picked_up == 1 and shape == 'c' && hand.canMove(x, y - 5))
                circles.y[pickme] -= 5;
            if (picked_up == 1 and shape == 't' && hand.canMove(x, y - 5))
                triangles.y[pickme] -= 5;
            else y = y;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;

        case VK_DOWN:// nie ma hitboxa dokończonego
            block = 0;
            if (picked_up == 1 and shape == 's' && hand.canMove(x, y + 5))
            {
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (boxes.y[pickme] == boxes.y[g] - 50 and boxes.x[pickme] > boxes.x[g] - 50 and boxes.x[pickme] < boxes.x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (boxes.y[pickme] == circles.y[g] - 50 and boxes.x[pickme] > circles.x[g] - 50 and boxes.x[pickme] < circles.x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    if (boxes.x[pickme] + 50 > triangles.x[g] - 25 and boxes.x[pickme] + 50 < triangles.x[g])
                    {
                        int wys = 2 * (-boxes.x[pickme] - 50 + triangles.x[g]);
                        if (boxes.y[pickme] + 50 >= triangles.y[g] + wys)
                            block = 1;
                    }
                    if (boxes.x[pickme] > triangles.x[g] and boxes.x[pickme] < triangles.x[g] + 25)
                    {
                        int wys = 2 * (boxes.x[pickme] - triangles.x[g]);
                        if (boxes.y[pickme] + 50 >= triangles.y[g] + wys)
                            block = 1;
                    }
                    if (boxes.x[pickme] + 50 > triangles.y[g] and boxes.x[pickme] < triangles.x[g] and boxes.y[pickme] + 50 == triangles.y[g])
                        block = 1;

                }
                if (block == 0)
                {
                    y = y + 5;
                    boxes.y[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 'c' && hand.canMove(x, y + 5))
            {
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (circles.y[pickme] == boxes.y[g] - 50 and circles.x[pickme] > boxes.x[g] - 50 and circles.x[pickme] < boxes.x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (circles.y[pickme] == circles.y[g] - 50 and circles.x[pickme] > circles.x[g] - 50 and circles.x[pickme] < circles.x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    if (circles.x[pickme] + 50 > triangles.x[g] - 25 and circles.x[pickme] + 50 < triangles.x[g])
                    {
                        int wys = 2 * (-circles.x[pickme] - 50 + triangles.x[g]);
                        if (circles.y[pickme] + 50 >= triangles.y[g] + wys)
                            block = 1;
                    }
                    if (circles.x[pickme] > triangles.x[g] and circles.x[pickme] < triangles.x[g] + 25)
                    {
                        int wys = 2 * (circles.x[pickme] - triangles.x[g]);
                        if (circles.y[pickme] + 50 >= triangles.y[g] + wys)
                            block = 1;
                    }
                    if (circles.x[pickme] + 50 > triangles.y[g] and circles.x[pickme] < triangles.x[g] and circles.y[pickme] + 50 == triangles.y[g])
                        block = 1;

                }
                if (block == 0)
                {
                    y = y + 5;
                    circles.y[pickme] += 5;
                }
            }
            if (picked_up == 1 and shape == 't' && hand.canMove(x, y + 5))
            {
                for (int g = 0; g < boxes.x.size(); g++)
                {
                    if (triangles.y[pickme] == boxes.y[g] - 50 and triangles.x[pickme] > boxes.x[g] - 50 and triangles.x[pickme] < boxes.x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < circles.x.size(); g++)
                {
                    if (triangles.y[pickme] == circles.y[g] - 50 and triangles.x[pickme] > circles.x[g] - 50 and triangles.x[pickme] < circles.x[g] + 50)
                        block = 1;
                }
                for (int g = 0; g < triangles.x.size(); g++)
                {
                    if (triangles.x[pickme] + 25 > triangles.x[g] - 25 and triangles.x[pickme] + 25 < triangles.x[g])
                    {
                        int wys = 2 * (-triangles.x[pickme] - 25 + triangles.x[g]);
                        if (triangles.y[pickme] + 50 >= triangles.y[g] + wys)
                            block = 1;
                    }
                    if (triangles.x[pickme] - 25 > triangles.x[g] and triangles.x[pickme] - 25 < triangles.x[g] + 25)
                    {
                        int wys = 2 * (triangles.x[pickme] - 25 - triangles.x[g]);
                        if (triangles.y[pickme] + 50 >= triangles.y[g] + wys)
                            block = 1;
                    }
                    if (triangles.x[pickme] + 25 > triangles.y[g] and triangles.x[pickme] - 25 < triangles.x[g] and triangles.y[pickme] + 50 == triangles.y[g])
                        block = 1;

                    if (block == 0)
                    {
                        y = y + 5;
                        triangles.y[pickme] += 5;
                    }
                }
            }
            if (picked_up == 0 && hand.canMove(x, y + 5))
                y = y + 5;
            else y = y;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;
        case VK_END:
            boxes.x.push_back(200);
            boxes.y.push_back(200);
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;
        case VK_DELETE:
            make_tower_2(hWnd, hdc, ps, NULL, x, y);
        case 0x0D:
            //kółka 
            for (int g = 0; g < circles.x.size(); g++)
            {
                if (y > circles.y[g] and y < circles.y[g] + 50)
                {
                    if (x >= circles.x[g] and x <= circles.x[g] + 50)
                    {
                        bool pod_spodem = 0;
                        for (int h = 0; h < circles.x.size(); h++)
                        {
                            if (circles.y[g] - 50 == circles.y[h] and circles.x[g] + 50 > circles.x[h] and circles.x[g] < circles.x[h] + 50)
                            {
                                pod_spodem = 1;
                            }
                        }

                        if (picked_up == 0 and hand.checkMass(circles.masa[g]) and pod_spodem == 0)
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

                            for (int h = 0; h < circles.y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (circles.y[pickme] != circles.y[h] and circles.x[pickme] - 50 <= circles.x[h] and circles.x[pickme] + 50 >= circles.x[h])
                                    {
                                        if (circles.y[h] == ground - 150)
                                        {
                                            tower = 1;
                                        }
                                        if (hight > circles.y[h])
                                            hight = circles.y[h];
                                    }
                                }
                            }
                            for (int h = 0; h < circles.y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (circles.y[g] != circles.y[h] and circles.x[g] - 50 <= circles.x[h] and circles.x[g] + 50 >= circles.x[h])
                                    {
                                        if (tower == 0 and diff == 0)
                                        {
                                            circles.y[g] = hight - 50;
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
                            for (int h = 0; h < boxes.y.size(); h++)
                            {

                                if (circles.x[g] + 50 >= boxes.x[h] and circles.x[g] <= boxes.x[h] + 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            //trójkąty
                            for (int h = 0; h < triangles.y.size(); h++)
                            {

                                if (circles.x[g] <= triangles.x[h] and circles.x[g] >= triangles.x[h] - 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            if (action == 0)
                                circles.y[g] = ground - 50;
                            repaintWindow(hWnd, hdc, ps, NULL, x, y);
                        }
                    }
                }
            }
            // kwadraty
            for (int g = 0; g < boxes.x.size(); g++)
            {
                if (y > boxes.y[g] and y < boxes.y[g] + 50)
                {
                    if (x >= boxes.x[g] and x <= boxes.x[g] + 50)
                    {
                        bool pod_spodem = 0;
                        for (int h = 0; h < boxes.x.size(); h++)
                        {
                            if (boxes.y[g] - 50 == boxes.y[h] and boxes.x[g] + 50 > boxes.x[h] and boxes.x[g] < boxes.x[h] + 50)
                            {
                                pod_spodem = 1;
                            }
                        }
                        if (picked_up == 0 and hand.checkMass(boxes.masa[g]) and pod_spodem == 0)
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
                            for (int h = 0; h < boxes.y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (boxes.y[g] != boxes.y[h] and boxes.x[g] - 50 <= boxes.x[h] and boxes.x[g] + 50 >= boxes.x[h])
                                    {
                                        if (boxes.y[h] == ground - 150)
                                        {
                                            tower = 1;
                                        }
                                        if (hight > boxes.y[h])
                                            hight = boxes.y[h];
                                    }
                                }
                            }
                            for (int h = 0; h < boxes.y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (boxes.y[g] != boxes.y[h] and boxes.x[g] - 50 <= boxes.x[h] and boxes.x[g] + 50 >= boxes.x[h])
                                    {
                                        if (tower == 0)
                                        {
                                            boxes.y[g] = hight - 50;
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
                            for (int h = 0; h < circles.y.size(); h++)
                            {

                                if (boxes.x[g] <= circles.x[h] and boxes.x[g] >= circles.x[h] - 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            //trójkąt
                            for (int h = 0; h < triangles.y.size(); h++)
                            {

                                if (boxes.x[g] <= triangles.x[h] and boxes.x[g] >= triangles.x[h] - 50)
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            if (action == 0)
                                boxes.y[g] = ground - 50;
                            repaintWindow(hWnd, hdc, ps, NULL, x, y);
                        }
                    }
                }
            }
            //trójkąty
            for (int g = 0; g < triangles.x.size(); g++)
            {
                if (y > triangles.y[g] and y < triangles.y[g] + 50)
                {
                    int szer = (y - triangles.y[g]) / 2;
                    if (x >= triangles.x[g] - szer and x <= triangles.x[g] + szer)
                    {
                        bool pod_spodem = 0;
                        for (int h = 0; h < triangles.x.size(); h++)
                        {
                            if (triangles.y[g] - 50 == triangles.y[h] and triangles.x[g] + 25 > triangles.x[h] - 25 and triangles.x[g] - 25 < triangles.x[h] + 25)
                            {
                                pod_spodem = 1;
                            }
                        }
                        if (picked_up == 0 and hand.checkMass(triangles.masa[g]) and pod_spodem == 0)
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
                            for (int h = 0; h < triangles.x.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (pickme != h and triangles.x[g] >= triangles.x[h] - 25 and triangles.x[g] <= triangles.x[h] + 25)
                                    {
                                        if (triangles.y[h] == ground - 150)
                                        {
                                            tower = 1;
                                        }
                                        if (hight > triangles.y[h])
                                            hight = triangles.y[h];
                                    }
                                }
                            }

                            for (int h = 0; h < triangles.y.size(); h++)
                            {
                                if (action == 0)
                                {
                                    if (triangles.y[pickme] != triangles.y[h] and triangles.x[pickme] >= triangles.x[h] - 25 and triangles.x[pickme] <= triangles.x[h] + 25)
                                    {
                                        if (tower == 0)
                                        {
                                            triangles.y[g] = hight - 50;
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
                            for (int h = 0; h < circles.x.size(); h++)
                            {

                                if (triangles.x[pickme] - 25 <= circles.x[h] + 50 and triangles.x[pickme] + 25 >= circles.x[h])
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }
                            //kwadrat
                            for (int h = 0; h < boxes.x.size(); h++)
                            {

                                if (triangles.x[pickme] - 25 <= boxes.x[h] + 50 and triangles.x[pickme] + 25 >= boxes.x[h])
                                {
                                    picked_up = 1;
                                    action = 1;
                                }
                            }

                            if (action == 0)
                                triangles.y[pickme] = ground - 50;
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
        if (bDrawCircle) circles.addNewShape(300, 200, 92);
        if (bDrawSquare) boxes.addNewShape(300, 200, 92);
        if (bDrawTriangle) triangles.addNewShape(300, 200, 92);
        drawBox(hdc, boxes);
        drawCircle(hdc, circles);
        drawTriangle(hdc, triangles);
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
