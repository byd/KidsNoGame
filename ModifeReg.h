//ModifeReg.h

#define data_Set "Software\\KillGame\\"
#define bootup_Set "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"

class CModifeReg
{
public:
	BOOL SetPassword(CString str){ return regSet("pass", str);}
	BOOL SetKeyword(CString str){ return regSet("keyword", str);}
	CString GetPassword(){ return regGet("pass");}
	CString GetKeyword(){ return regGet("keyword");}
	
	BOOL ClearAll(){ 
		HKEY hKEY;

		long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\",0,KEY_ALL_ACCESS,&hKEY));
		if(ret0!=ERROR_SUCCESS) return FALSE;
		::RegDeleteKey(hKEY,"KillGame");

		HKEY myKEY;
		ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,bootup_Set,0,KEY_ALL_ACCESS,&myKEY));
		if(ret0!=ERROR_SUCCESS) return FALSE;
		::RegDeleteValue(myKEY, "KillGame");
		::RegCloseKey(myKEY);

		return TRUE;
	}

	BOOL setStartUp()
	{
		HKEY hKey; 
		long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, bootup_Set, 0, KEY_WRITE, &hKey); 
		if(lRet == ERROR_SUCCESS) 
		{ 
			char pFileName[MAX_PATH] = {0}; 
			//�õ����������ȫ·�� 
			DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH); 
			//���һ����Key,������ֵ // �����"getip"��Ӧ�ó������֣����Ӻ�׺.exe��
			lRet = RegSetValueEx(hKey, "KillGame", 0, REG_SZ, (BYTE *)pFileName, dwRet); 

			//�ر�ע��� 
			RegCloseKey(hKey); 
			if(lRet != ERROR_SUCCESS) 
			{ 
				AfxMessageBox("ϵͳ��������,������ϵͳ����"); 
			}
		} 
		return TRUE;
	}

private:

	/*����ע���ֵ*/
	BOOL regSet(CString item, CString str, LPCTSTR set = data_Set)
	{
		HKEY myKey;
		unsigned long type;

		long ret=(::RegCreateKeyEx(HKEY_LOCAL_MACHINE,
			set,0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS|KEY_READ|KEY_WRITE,
			NULL,
			&myKey,
			&type));

		if(ret!=ERROR_SUCCESS) return FALSE;

		//��1Ϊ�ַ������Ŀ��ַ�/0���ռ�
		LPBYTE lpData = new BYTE[str.GetLength()+1];
		for(int i = 0; i < str.GetLength(); i++)
		{
			*(lpData+i) = str.GetAt(i);
		}
		DWORD cbData = str.GetLength()+1;
		

		CString seeStr = CString(lpData);

		//����ֵ
		if(RegSetValueEx(myKey,_T(item),
			0,REG_SZ,lpData,cbData) != ERROR_SUCCESS)
			return FALSE;
		delete [] lpData;

		::RegCloseKey(myKey);
		return TRUE;
	}


	/*�õ�ע���ֵ*/

	CString regGet(CString item)
	{
		HKEY hKEY;

		long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set,0,KEY_READ,&hKEY));
		if(ret0!=ERROR_SUCCESS) return "";
    
		LPBYTE cRet=new BYTE[80];//�����û����� owner_Get
		DWORD type_1=REG_SZ;  //������������
		DWORD cbData_1=80;  //�������ݳ���
		long ret1=::RegQueryValueEx(hKEY,item,NULL,&type_1,cRet,&cbData_1);
		if(ret1!=ERROR_SUCCESS) return "";
    
		CString strRet = CString(cRet);
		delete[] cRet;
		::RegCloseKey(hKEY);

		return CString(strRet);
	}
};

