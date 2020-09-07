#include "StdAfx.h"
#include "NILayer.h"
CNILayer::CNILayer( char* pName ) : CBaseLayer( pName )
{

}

CNILayer::~CNILayer()
{

}

void CNILayer::SetDevice(pcap_if_t *DeviceList,int dev_num)
{
	//Dlg �������� �� �Լ��� �ҷ��� - �� �Լ��� ���� ������ Dlg���� ���õ� Device�� �������� ���ؼ�
	char ebuf[30];
	this->DeviceList[dev_num-1] = DeviceList;
	this->Device[dev_num-1] = pcap_open_live(this->DeviceList[dev_num-1]->name , 1500 , 1 , 1 , ebuf);
}

BOOL CNILayer::Send(unsigned char* ppayload, int nlength,int dev_num)
{
	// ��Ŷ�� ������ �κ� - ppayload�� �������� packet�̵ǰ� ũ��� nlength 
	if(Device != NULL && pcap_sendpacket(Device[dev_num-1] , ppayload , nlength ) == 0)
	{
		return TRUE;
	}
	else
	{
		AfxMessageBox( "sendpacket error!", MB_OK | MB_ICONSTOP ) ;	// ���н� �޼���â ���
		return FALSE;
	}
}

BOOL CNILayer::Receive(int dev_num)
{
	int result;
	result = pcap_next_ex(Device[dev_num-1],&pkt_header[dev_num-1],(const unsigned char **)&pkt_data[dev_num-1]);
	if(result == 1)
	{
		mp_aUpperLayer[0]->Receive(pkt_data[dev_num-1],dev_num);	// ���� �������� ������
		return TRUE;
	}
	mutex.Unlock();
	return FALSE;
}

void CNILayer::StartReadThread()
{
	// Dlg ���� ���� �ҷ����� �Լ�, �����带 �����Ѵ�
	pThread_1 = AfxBeginThread(WaitPacket_1 , this);
	pThread_2 = AfxBeginThread(WaitPacket_2 , this);
	if(pThread_1 == NULL || pThread_2 == NULL)
	{
		AfxMessageBox("Read ������ ���� ����");
	}
}

unsigned int CNILayer::WaitPacket_1(LPVOID pParam) 
{
	// ������� ����Ǵ� �Լ� - ��Ŷ�� �޾��� ��� ���� �������� ������ ���� Receive �Լ��� ȣ���ؼ� ��Ŷ�� �޴´�.
	CNILayer *temp_NILayer = (CNILayer*)pParam;
	int result;
	while(1)
	{
		temp_NILayer->Receive(1);
	}
	return 0;
}

unsigned int CNILayer::WaitPacket_2(LPVOID pParam)
{
	// ������� ����Ǵ� �Լ� - ��Ŷ�� �޾��� ��� ���� �������� ������ ���� Receive �Լ��� ȣ���ؼ� ��Ŷ�� �޴´�.
	CNILayer *temp_NILayer = (CNILayer*)pParam;
	int result;
	while(1)
	{
		temp_NILayer->Receive(2);
	}
	return 0;
}