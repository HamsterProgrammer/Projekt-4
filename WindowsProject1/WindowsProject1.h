#pragma once
#include "Resource.h"
#include "framework.h"
#include <vector>
#include <sstream>
#include <cstdio>
#include <random> 
#include <windows.h>
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

static INT_PTR CALLBACK SetMassDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hwndButton;
int x = 20;
int y = 100;
int ground = 250;
bool picked_up = 0;
int pickme = 0;
char shape;
bool block = 0;

class RoboHand {
public:
	int x, y;       //coordinates now
	const int xMin = 0, xMax = 1000; //range of x
	const int yMin=0, yMax=250; //range of y
	int maxMass = 98;
	bool put;
	bool stanB;
	bool stanT;
	bool stanC;
	bool canMove(int newX, int newY) {
		if (newX >= xMin && newX <= xMax && newY >= yMin && newY <= yMax) {
			x = newX;
			y = newY;
			return true;
		}
		else return false;
	}
	int setX(int newX) {
		if (canMove(newX, y)) {
			x = newX;
			return x;
		}
	}
	int setY(int newY) {
		if (canMove(x, newY)) {
			y = newY;
			return y;
		}
	}
	int setMaxMass(int newMaxMass) {
		maxMass = newMaxMass;
		return maxMass;
	}
	bool checkMass(int currentMass) {
		if (currentMass <= maxMass) return true;
		else return false;
	}

};

class Shapes {
//initialization of figures, add a funktion that will give you an additional figures
public:
	std::vector<int> x = {};
	std::vector<int> y = {};
	std::vector<int> masa = {};

	void addNewShape(int x0, int y0, int masa0) {
		x.push_back(x0);
		y.push_back(y0);
		masa.push_back(masa0);
	}
};
