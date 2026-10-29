void FUN_00732210(void)

{
  UINT UVar1;
  char *pcVar2;
  DWORD DVar3;
  DWORD DVar4;
  undefined4 uVar5;
  HWND hWnd;
  int iVar6;
  CHAR *pCVar7;
  char local_ac;
  undefined1 local_ab [127];
  CHAR local_2c [36];
  undefined4 local_8;

  local_8 = DAT_00c02edc ^ (uint)(local_2c + 0x28);
  pcVar2 = "./DataTable/ClientSystem.ini";
  pCVar7 = local_2c;
  for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
    *(undefined4 *)pCVar7 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pCVar7 = pCVar7 + 4;
  }
  *pCVar7 = *pcVar2;
  local_ac = '\0';
  _memset(local_ab,0,0x7f);
  UVar1 = GetPrivateProfileIntA("Network","ConnectTime",0x5a,local_2c);
  iVar6 = FUN_00541020(1,0);
  if (iVar6 == 0) {
    FUN_005b1510("Connect World....True.. WaitingFor...");
    DVar3 = timeGetTime();
    while( true ) {
      DVar4 = timeGetTime();
      FUN_0080a6a0();
      iVar6 = FUN_0051c290(1);
      if (iVar6 != 0) break;
      if (UVar1 * 1000 < DVar4 - DVar3) {
        uVar5 = Ordinal_111();
        pcVar2 = (char *)FUN_005ca6a0(0xbfa);
        _sprintf(&local_ac,pcVar2,uVar5);
        FUN_005b1510(&local_ac);
        iVar6 = 0;
        hWnd = (HWND)FUN_004093f0();
        ShowWindow(hWnd,iVar6);
        MessageBoxA((HWND)0x0,&local_ac,(LPCSTR)0x0,0);
        goto LAB_007323d9;
      }
      Sleep(4);
    }
    FUN_005b1510("IsConnectedToServer TRUE");
  }
  else {
    FUN_005b1510("World Server Connect Faile %d",iVar6);
    pcVar2 = (char *)FUN_005ca6a0(0x6be);
    _sprintf(&local_ac,pcVar2,iVar6);
    MessageBoxA((HWND)0x0,&local_ac,(LPCSTR)0x0,0);
  }
LAB_007323d9:
  __security_check_cookie(local_8 ^ (uint)(local_2c + 0x28));
  return;
}
