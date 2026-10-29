void FUN_00538c00(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_e8;
  char local_9c [128];
  int local_1c;
  void *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;

  local_8 = 0xffffffff;
  puStack_c = &LAB_00acb90c;
  local_10 = ExceptionList;
  local_14 = DAT_00c02edc ^ (uint)(local_9c + 0x98);
  ExceptionList = &local_10;
  FUN_0053de60(local_14);
  local_8 = 0;
  _memset(local_18,0,0x560);
  for (local_1c = 0; local_1c < 100; local_1c = local_1c + 1) {
    *(undefined4 *)((int)local_18 + local_1c * 8 + 0x10) = 0xffffffff;
    *(undefined4 *)((int)local_18 + local_1c * 8 + 0x14) = 0xffffffff;
  }
  iVar1 = FUN_007b14e8(0x10);
  local_8._0_1_ = 1;
  if (iVar1 == 0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_0053df80();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  *(undefined4 *)((int)local_18 + 0x338) = local_e8;
  *(undefined4 *)((int)local_18 + 0x33c) = 0;
  *(undefined4 *)((int)local_18 + 0x340) = 0;
  *(undefined2 *)((int)local_18 + 0x344) = 0;
  uVar2 = FUN_005b0f90();
  _sprintf(local_9c,"%s\\KeyMap.dat",uVar2);
  FUN_007b2650((int)local_18 + 0x346,local_9c);
  uVar2 = FUN_005b0f90();
  _sprintf(local_9c,"%s\\KeyMap_NKM.dat",uVar2);
  FUN_007b2650((int)local_18 + 0x44a,local_9c);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)(local_9c + 0x98));
  return;
}
