#pragma once

// CSimpleEditDlg 对话框

class CSimpleEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimpleEditDlg)

public:
	CSimpleEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSimpleEditDlg();

// 对话框数据
	enum { IDD = IDD_SIMPLE_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
