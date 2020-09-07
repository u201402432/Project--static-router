#pragma once
#include "afxcmn.h"
#include "afxwin.h"
// CRoutTableAdder ��ȭ �����Դϴ�.

class CRoutTableAdder : public CDialog
{
	DECLARE_DYNAMIC(CRoutTableAdder)

public:
	CRoutTableAdder();   // ǥ�� �������Դϴ�.
	virtual ~CRoutTableAdder();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ROUTE_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString d1,d2;
	void setDeviceList(CString dev1,CString dev2);
	unsigned char dest_ip[4];
	unsigned char net_ip[4];
	unsigned char gate_ip[4];
	unsigned char flag;
	int router_interface;
	// routetableDestination �߰�
	CIPAddressCtrl m_add_dest;
	CIPAddressCtrl m_add_netmask;
	CIPAddressCtrl m_gateway;
	CComboBox m_add_interface;

	CButton m_flag_u;
	CButton m_flag_g;
	CButton m_flag_h;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	// get destination 
	unsigned char * GetDestIp(void);
	// get netmask
	unsigned char * GetNetmask(void);
	// get Gateway
	unsigned char * GetGateway(void);
	// get inter face
	int GetInterface(void);
	// get metric
	int GetMetric(void);
	// get flag
	unsigned char GetFlag(void);
	int m_metric;
};
