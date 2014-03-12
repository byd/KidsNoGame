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
			//得到程序自身的全路径 
			DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH); 
			//添加一个子Key,并设置值 // 下面的"getip"是应用程序名字（不加后缀.exe）
			lRet = RegSetValueEx(hKey, "KillGame", 0, REG_SZ, (BYTE *)pFileName, dwRet); 

			//关闭注册表 
			RegCloseKey(hKey); 
			if(lRet != ERROR_SUCCESS) 
			{ 
				AfxMessageBox("系统参数错误,不能随系统启动"); 
			}
		} 
		return TRUE;
	}

private:

	/*设置注册表值*/
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

		//加1为字符串最后的空字符/0留空间
		LPBYTE lpData = new BYTE[str.GetLength()+1];
		for(int i = 0; i < str.GetLength(); i++)
		{
			*(lpData+i) = str.GetAt(i);
		}
		DWORD cbData = str.GetLength()+1;
		

		CString seeStr = CString(lpData);

		//设置值
		if(RegSetValueEx(myKey,_T(item),
			0,REG_SZ,lpData,cbData) != ERROR_SUCCESS)
			return FALSE;
		delete [] lpData;

		::RegCloseKey(myKey);
		return TRUE;
	}


	/*得到注册表值*/

	CString regGet(CString item)
	{
		HKEY hKEY;

		long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set,0,KEY_READ,&hKEY));
		if(ret0!=ERROR_SUCCESS) return "";
    
		LPBYTE cRet=new BYTE[80];//定义用户姓名 owner_Get
		DWORD type_1=REG_SZ;  //定义数据类型
		DWORD cbData_1=80;  //定义数据长度
		long ret1=::RegQueryValueEx(hKEY,item,NULL,&type_1,cRet,&cbData_1);
		if(ret1!=ERROR_SUCCESS) return "";
    
		CString strRet = CString(cRet);
		delete[] cRet;
		::RegCloseKey(hKEY);

		return CString(strRet);
	}
};

