
// imageProcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CimageProcDlg �Ի���
class CimageProcDlg : public CDialogEx
{
// ����
public:
	CimageProcDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void Display(int HWND,BITMAPINFO* pDisBmpInfo,BYTE* pDisBmpData);

// �Ի�������
	enum { IDD = IDD_imageProc_DIALOG };

protected:
	CWinThread* pThread1;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedFix1();
	
	CProgressCtrl m_process1;
};

UINT ThreadFunc1(LPVOID lpParam);

