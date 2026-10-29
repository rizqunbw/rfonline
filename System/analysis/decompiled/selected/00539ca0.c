/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x00539ca0. */

void FUN_00539ca0(char *param_1,int *param_2)

{
  int iVar1;
  undefined1 local_30 [32];
  undefined4 local_10;
  undefined4 local_8;

  local_8 = DAT_00c02edc ^ (uint)(local_30 + 0x2c);
  if (param_2 != (int *)0x0) {
    local_10 = 0x20;
    _memset(local_30,0,0x20);
    FUN_00539d80(local_30,param_2[1]);
    iVar1 = *param_2;
    if (iVar1 == 0x10) {
      _sprintf(param_1,"SHIFT+%s",local_30);
    }
    else if (iVar1 == 0x11) {
      _sprintf(param_1,"CTRL+%s",local_30);
    }
    else if (iVar1 == 0x12) {
      _sprintf(param_1,"ALT+%s",local_30);
    }
    else {
      _sprintf(param_1,"%s",local_30);
    }
  }
  __security_check_cookie(local_8 ^ (uint)(local_30 + 0x2c));
  return;
}
