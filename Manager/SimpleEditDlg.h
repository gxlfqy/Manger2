#pragma once

// CSimpleEditDlg �Ի���

class CSimpleEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimpleEditDlg)

public:
	CSimpleEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSimpleEditDlg();

// �Ի�������
	enum { IDD = IDD_SIMPLE_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
