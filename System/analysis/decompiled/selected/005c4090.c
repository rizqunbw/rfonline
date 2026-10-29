/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x005c4090. */

void FUN_005c4090(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined4 local_11c [8];
  undefined1 local_fc [232];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;

  local_8 = 0xffffffff;
  puStack_c = &LAB_00ad0d2b;
  local_10 = ExceptionList;
  uVar1 = DAT_00c02edc ^ (uint)(local_fc + 0xf8);
  ExceptionList = &local_10;
  pcVar4 = ".\\DataTable\\PlayerCharacter.edf";
  puVar5 = local_11c;
  local_14 = uVar1;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    puVar5 = puVar5 + 1;
  }
  _memset(local_fc,0,0xe4);
  FUN_005b79b0(local_11c);
  local_8 = 0;
  iVar3 = FUN_0048bb50(uVar1);
  if (iVar3 == 0) {
    local_8 = 0xffffffff;
    FUN_005b7940();
  }
  else {
    iVar2 = FUN_0048bb30();
    if (iVar2 == 0) {
      local_8 = 0xffffffff;
      FUN_005b7940();
    }
    else {
      FUN_005b9a60(iVar3);
      local_8 = 0xffffffff;
      FUN_005b7940();
    }
  }
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)(local_fc + 0xf8));
  return;
}
