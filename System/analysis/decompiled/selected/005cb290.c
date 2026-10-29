/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x005cb290. */

void FUN_005cb290(void)

{
  undefined4 uVar1;
  int iVar2;
  uint local_258;
  char local_11c [260];
  int *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;

  local_8 = 0xffffffff;
  puStack_c = &LAB_00ad132b;
  local_10 = ExceptionList;
  local_14 = DAT_00c02edc ^ (uint)(local_11c + 0x118);
  ExceptionList = &local_10;
  uVar1 = FUN_005b0fd0(local_14);
  _sprintf(local_11c,".\\DataTable\\%s\\NDLanguage.edf",uVar1);
  FUN_005b79b0(local_11c);
  local_8 = 0;
  FUN_0048bb50();
  FUN_005b77a0(local_18 + 2,4,1);
  if (local_18[2] == 0) {
    local_8 = 0xffffffff;
    FUN_005b7940();
  }
  else {
    iVar2 = thunk_FUN_007b14e8(-(uint)((int)((ulonglong)(uint)local_18[2] * 0xc >> 0x20) != 0) |
                               (uint)((ulonglong)(uint)local_18[2] * 0xc));
    *local_18 = iVar2;
    for (local_258 = 0; local_258 < (uint)local_18[2]; local_258 = local_258 + 1) {
      iVar2 = local_258 * 0xc + *local_18;
      if (iVar2 != 0) {
        FUN_005b77a0(iVar2,4,1);
        FUN_005b77a0(iVar2 + 4,4,1);
        uVar1 = thunk_FUN_007b14e8(*(undefined4 *)(iVar2 + 4));
        *(undefined4 *)(iVar2 + 8) = uVar1;
        FUN_005b77a0(*(undefined4 *)(iVar2 + 8),1,*(undefined4 *)(iVar2 + 4));
      }
    }
    local_8 = 0xffffffff;
    FUN_005b7940();
  }
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)(local_11c + 0x118));
  return;
}
