// SearchingForm.h
#ifndef _SEARCHINGFORM_H
#define _SEARCHINGFORM_H
#include <Windows.h>

BOOL CALLBACK SearchingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL SearchingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL SearchingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL SearchingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL SearchingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL SearchingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL SearchingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif // _SEARCHINGFORM_H