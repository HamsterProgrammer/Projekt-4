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
    boxes.addNewShape(700, 200, 96);
    boxes.addNewShape(400, 200, 90);
    boxes.addNewShape(770, 200, 99);
    //initialization of roboHand (dzwig)
    hand.x = 20;
    hand.y = 50;
    hand.put = false;

    hand.stanB = false;
    hand.stanC = false;
    hand.stanT = false;
}

int getRandomMass() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0, 150);
    int randomNumber = dist(engine);
    if (randomNumber < 40) randomNumber = 2 * randomNumber;
    return randomNumber;
}

int getRandomNumber() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0, 1000);
    int randomNumber = dist(engine);

    return randomNumber;
}
void MyOnPaint(HDC hdc, int x, int y)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 0, 0, 255));
    if (hand.canMove(x, y)) {
        hand.setX(x);
        hand.setY(y);
        graphics.DrawLine(&pen, hand.x, 10, hand.x, hand.y);      
    }
}
std::vector<int> wierzcholki{ {4} };     

void drawBox(HDC hdc, Shapes &boxes)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    Font font(L"Arial", 12);
    SolidBrush brush(Color(255, 0, 0, 0));
    if (bDrawSquare) {
        boxes.addNewShape(getRandomNumber(), 200, getRandomMass());
        bDrawSquare = false;
    }
    for (int g = 0; g < boxes.x.size(); g++)
    {
        int centerX = boxes.x[g] + 25; 
        int centerY = boxes.y[g] + 25; 

        graphics.DrawRectangle(&pen, boxes.x[g], boxes.y[g], 50, 50);

        std::wstringstream wss;
        wss << boxes.masa[g];  

        std::wstring text = wss.str(); 

        graphics.DrawString(text.c_str(), -1, &font, PointF(centerX, centerY), &brush);
    }
}
void drawTriangle(HDC hdc, Shapes &triangles)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    Font font(L"Arial", 12);
    SolidBrush brush(Color(255, 0, 0, 0));
    if (bDrawTriangle) {
        triangles.addNewShape(getRandomNumber(), 200, getRandomMass());
        bDrawTriangle = false;
    }
    for (int g = 0; g < triangles.x.size(); g++)
    {
        graphics.DrawLine(&pen, triangles.x[g], triangles.y[g], triangles.x[g] - 25, triangles.y[g] + 50);
        graphics.DrawLine(&pen, triangles.x[g], triangles.y[g], triangles.x[g] + 25, triangles.y[g] + 50);
        graphics.DrawLine(&pen, triangles.x[g] - 25, triangles.y[g] + 50, triangles.x[g] + 25, triangles.y[g] + 50);

        int centerX = (triangles.x[g] + triangles.x[g] - 25 + triangles.x[g] + 25) / 3;
        int centerY = triangles.y[g] + 30; 

        std::wstringstream wss;
        wss << triangles.masa[g];  

        std::wstring text = wss.str();  

        graphics.DrawString(text.c_str(), -1, &font, PointF(centerX, centerY), &brush);
    }
}

void drawCircle(HDC hdc, Shapes &circles)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 0, 0));
    Font font(L"Arial", 12);
    SolidBrush brush(Color(255, 0, 0, 0));
    if (bDrawCircle) {
        circles.addNewShape(getRandomNumber(), 200, getRandomMass());
        bDrawCircle = false;
    }
    for (int g = 0; g < circles.x.size(); g++)
    {
        graphics.DrawArc(&pen, circles.x[g], circles.y[g], 50, 50, 0, 360);

        int centerX = circles.x[g] + 25;
        int centerY = circles.y[g] + 25;

        std::wstringstream wss;
        wss << circles.masa[g];  

        std::wstring text = wss.str(); 

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

bool under_smth(Shapes shape, int id) {
    for (int i = 0; i < boxes.x.size(); i++) {
        if ((shape.x[id] == boxes.x[i]) || (shape.x[id] + 50 >= boxes.x[i] && shape.x[id] <= boxes.x[i]) || (shape.x[id] >= boxes.x[i] && shape.x[id] <= boxes.x[i] + 50)) {
            if (shape.y[id] > boxes.y[i])
                return true;
        }
    }
    for (int i = 0; i < circles.x.size(); i++) {
        if ((shape.x[id] == circles.x[i]) || (shape.x[id] + 50 >= circles.x[i] && shape.x[id] <= circles.x[i]) || (shape.x[id] >= circles.x[i] && shape.x[id] <= circles.x[i] + 50)) {
            if (shape.y[id] > circles.y[i])
                return true;
        }
    }
    for (int i = 0; i < triangles.x.size(); i++) {
        if ((shape.x[id] == triangles.x[i]) || (shape.x[id] + 50 >= triangles.x[i] && shape.x[id] <= triangles.x[i]) || (shape.x[id] >= triangles.x[i] && shape.x[id] <= triangles.x[i] + 50)) {
            if (shape.y[id] > triangles.y[i])
                return true;
        }
    }
    return false;
}

int chooseRandomShape(Shapes shape) {
    //check mass, under_smth or not
    for (int i = 0; i < shape.x.size(); i++) {
        if (under_smth(shape, i)) continue;
        else if (hand.checkMass(shape.masa[i])) {
            return i;
        }
    }
}

void make_tower_1(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int& x, int& y)
{
    int gB = chooseRandomShape(boxes);
    int gC = chooseRandomShape(circles);
    int gT = chooseRandomShape(triangles);
    while (x != boxes.x[gB] && hand.canMove(x + 5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != boxes.y[gB] && hand.canMove(x, y + 5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y - 5))
    {
        y -= 5;
        boxes.y[gB] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20 && hand.canMove(x - 5, y))
    {
        x -= 5;
        boxes.x[gB] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    boxes.y[gB] = 200;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != triangles.x[gT] && hand.canMove(x + 5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != triangles.y[gT] && hand.canMove(x, y + 5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y - 5))
    {
        y -= 5;
        triangles.y[gT] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20 + 25 && hand.canMove(x - 5, y))
    {
        x -= 5;
        triangles.x[gT] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    triangles.y[gT] = 150;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != circles.x[gC] && hand.canMove(x + 5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != circles.y[gC] && hand.canMove(x, y + 5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y - 5))
    {
        y -= 5;
        circles.y[gC] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 20 && hand.canMove(x - 5, y))
    {
        x -= 5;
        circles.x[gC] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    circles.y[gC] = 100;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);
}

void make_tower_2(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, int& x, int& y)
{
    int gB = chooseRandomShape(boxes);
    int gC = chooseRandomShape(circles);
    int gT = chooseRandomShape(triangles);
    while (x != circles.x[gC] && hand.canMove(x + 5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != circles.y[gC] && hand.canMove(x, y + 5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y - 5))
    {
        y -= 5;
        circles.y[gC] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 60 && hand.canMove(x - 5, y))
    {
        x -= 5;
        circles.x[gC] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    circles.y[gC] = 200;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != boxes.x[gB] && hand.canMove(x + 5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != boxes.y[gB] && hand.canMove(x, y + 5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y - 5))
    {
        y -= 5;
        boxes.y[gB] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 60 && hand.canMove(x, y - 5))
    {
        x -= 5;
        boxes.x[gB] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    boxes.y[gB] = 150;
    repaintWindow(hWnd, hdc, ps, drawArea, x, y);

    while (x != triangles.x[gT] && hand.canMove(x + 5, y))
    {
        x += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != triangles.y[gT] && hand.canMove(x, y + 5))
    {
        y += 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (y != 100 && hand.canMove(x, y - 5))
    {
        y -= 5;
        triangles.y[gT] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }
    while (x != 60 + 25 && hand.canMove(x - 5, y))
    {
        x -= 5;
        triangles.x[gT] -= 5;
        repaintWindow(hWnd, hdc, ps, drawArea, x, y);
    }

    triangles.y[gT] = 100;
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
            bDrawCircle = true;
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_TRIANGLE:
            bDrawTriangle =true;
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_SQUARE:
            bDrawSquare = true;
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_NOLIMITS:
            hand.stanB = false;
            hand.stanC = false;
            hand.stanT = false;
            break;
        //case IDM_ONLYBOXES:   
        //    hand.stanB = true;
        //    hand.stanC = false;
        //    hand.stanT = false;
        //    break;
        //case IDM_ONLYCIRCLES:
        //    hand.stanC = true;
        //    hand.stanB = false;
        //    hand.stanT = false;
        //    break;        
        //case IDM_ONLYTRIANGLES:
        //    hand.stanT = true;
        //    hand.stanB = false;
        //    hand.stanC = false;
        //    break;
        case IDM_TOWERCBT:
            make_tower_2(hWnd, hdc, ps, NULL, x, y);
            break;
        case IDM_TOWERBCT:
            make_tower_1(hWnd, hdc, ps, NULL, x, y);
            break;
        case IDM_SETMASS:
        {
            INT_PTR result = DialogBox(hInst, MAKEINTRESOURCE(IDD_SET_MASS_DIALOG), hWnd, SetMassDialogProc);
            if (result == IDOK){}
            break;
        }
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
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
                if (block == 0 && hand.canMove(x-5, y))
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
                if (block == 0 && hand.canMove(x-5, y))
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
            if (picked_up == 0 && hand.canMove(x-5, y)) {
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
                if (block == 0 && hand.canMove(x+5, y))
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
                if (block == 0 && hand.canMove(x+5, y))
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
                if (block == 0 && hand.canMove(x+5, y))
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

        case VK_DOWN:
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
                if (boxes.y[pickme] + 50 == ground)
                    block = 1;
                if (block == 0 && hand.canMove(x, y + 5))
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
                if (circles.y[pickme] + 50 == ground)
                    block = 1;
                if (block == 0 && hand.canMove(x, y + 5))
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
                }
                    if (triangles.y[pickme] + 50 == ground)
                        block = 1;
                    if (block == 0 && hand.canMove(x, y + 5))
                    {
                        y = y + 5;
                        triangles.y[pickme] += 5;
                    }
                
            }
            if (picked_up == 0 && hand.canMove(x, y + 5))
                y = y + 5;
            else
                y = y;
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;
        case VK_END:
            boxes.x.push_back(200);
            boxes.y.push_back(200);
            repaintWindow(hWnd, hdc, ps, NULL, x, y);
            break;
        case VK_DELETE:
            make_tower_2(hWnd, hdc, ps, NULL, x, y);
            break;
        case 0x0D:
            //kółka 
            if(!hand.stanB && !hand.stanT)
            for (int g = 0; g < circles.x.size(); g++)
            {
                if (y > circles.y[g] and y < circles.y[g] + 50)
                {
                    if (x >= circles.x[g] and x <= circles.x[g] + 50)
                    {
                        bool pod_spodem = under_smth(circles, g);

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
            if(!hand.stanC && !hand.stanT)
            for (int g = 0; g < boxes.x.size(); g++)
            {
                if (y > boxes.y[g] and y < boxes.y[g] + 50)
                {
                    if (x >= boxes.x[g] and x <= boxes.x[g] + 50)
                    {
                        bool pod_spodem = under_smth(boxes, g);
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
            if(!hand.stanC && !hand.stanC)
            for (int g = 0; g < triangles.x.size(); g++)
            {
                if (y > triangles.y[g] and y < triangles.y[g] + 50)
                {
                    int szer = (y - triangles.y[g]) / 2;
                    if (x >= triangles.x[g] - szer and x <= triangles.x[g] + szer)
                    {
                        bool pod_spodem = under_smth(triangles, g);
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

// Message handler for about box

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

static INT_PTR CALLBACK SetMassDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:

        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            HWND hMassEdit = GetDlgItem(hwndDlg, IDC_MASS_EDIT);
            wchar_t massText[256];
            GetWindowTextW(hMassEdit, massText, sizeof(massText) / sizeof(massText[0]));

            int newMaxMass = _wtoi(massText);

            hand.setMaxMass(newMaxMass);

            EndDialog(hwndDlg, IDOK);
            return TRUE;
        }

        case IDCANCEL:
            EndDialog(hwndDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }

    return FALSE;
}
