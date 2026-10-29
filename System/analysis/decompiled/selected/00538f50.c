/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x00538f50. */

undefined4 FUN_00538f50(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_c;

  local_c = 0;
  do {
    if (2 < local_c) {
LAB_00538fb3:
      local_c = 0;
      while( true ) {
        if (0x55 < local_c) {
          return 0;
        }
        uVar1 = FUN_00513770(param_3,&DAT_00b06d30 + local_c * 0xc);
        iVar2 = FUN_00429190(uVar1);
        if (iVar2 == 0) break;
        local_c = local_c + 1;
      }
      param_1[1] = *(undefined4 *)(&DAT_00b07138 + local_c * 4);
      return 1;
    }
    uVar1 = FUN_00513770(param_2,"SHIFT" + local_c * 0xc);
    iVar2 = FUN_00429190(uVar1);
    if (iVar2 == 0) {
      *param_1 = *(undefined4 *)(&DAT_00b06d24 + local_c * 4);
      goto LAB_00538fb3;
    }
    local_c = local_c + 1;
  } while( true );
}
