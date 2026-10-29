/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005286a0(void)

{
  UINT UVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  CHAR *pCVar7;
  float10 fVar8;
  undefined1 *puVar9;
  undefined *puVar10;
  int local_30;
  uint local_2c;
  CHAR local_28 [32];
  undefined4 local_8;

  local_8 = DAT_00c02edc ^ (uint)(local_28 + 0x24);
  pcVar6 = "./DataTable/GameSetting.ini";
  pCVar7 = local_28;
  for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined4 *)pCVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pCVar7 = pCVar7 + 4;
  }
  UVar1 = GetPrivateProfileIntA("Performance","AutoVisualFieldAdjustment",0,local_28);
  FUN_005090b0(UVar1);
  UVar1 = GetPrivateProfileIntA("Performance","VisualFieldAdjustmentLevel",5,local_28);
  FUN_00509100(UVar1);
  local_2c = GetPrivateProfileIntA("Camera","Mode",1,local_28);
  if (4 < (int)local_2c) {
    local_2c = 1;
  }
  FUN_0072a6b0(local_2c & 0xff);
  FUN_00419d60(1);
  FUN_00419d90(300000);
  piVar2 = (int *)FUN_007754c0(1);
  (**(code **)(*piVar2 + 0x50))(DAT_0240f0c4);
  fVar8 = (float10)FUN_0081a820();
  FUN_006ab300(0,(float)fVar8);
  fVar8 = (float10)FUN_0081a7e0();
  FUN_006ab300(1,(float)fVar8);
  fVar8 = (float10)FUN_0081a800();
  FUN_006ab300(2,(float)fVar8);
  FUN_006ab670(1);
  FUN_006ab700(1);
  FUN_006ab3f0(0,_DAT_02515038);
  local_30 = _DAT_0251504c;
  if (_DAT_0251504c == 0) {
    FUN_00737ed0(1);
    uVar3 = FUN_005ca6a0(DAT_00bdf0d0);
    uVar4 = FUN_005ca6a0(0xade);
    FUN_005af330(uVar4,uVar3);
  }
  else if (_DAT_0251504c < 5) {
    FUN_00737ed0(1);
    puVar9 = &DAT_00b0621c;
    uVar3 = FUN_005ca6a0(0xade);
    FUN_005af330(uVar3,puVar9);
    local_30 = 1;
  }
  else if (_DAT_0251504c == 6) {
    puVar10 = &DAT_00b06218;
    uVar3 = FUN_005ca6a0(0xade);
    FUN_005af330(uVar3,puVar10);
    local_30 = 2;
  }
  else if (9 < _DAT_0251504c) {
    uVar3 = FUN_005ca6a0(DAT_00bdf0d4);
    uVar4 = FUN_005ca6a0(0xade);
    FUN_005af330(uVar4,uVar3);
    local_30 = 3;
  }
  FUN_006ab3f0(1,(float)local_30);
  FUN_006ab3f0(5,_DAT_00b00d3c);
  local_30 = DAT_02515048;
  if (DAT_02515048 == 10) {
    local_30 = 2;
  }
  if ((local_30 < 0) || (9 < local_30)) {
    local_30 = 3;
  }
  FUN_006ab3f0(2,(float)local_30);
  FUN_006ab3f0(4,(float)DAT_02515070);
  __security_check_cookie(local_8 ^ (uint)(local_28 + 0x24));
  return;
}
