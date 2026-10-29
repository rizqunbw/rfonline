/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x00539020. */

void FUN_00539020(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_4c [32];
  undefined1 local_2c [36];
  undefined4 local_8;

  local_8 = DAT_00c02edc ^ (uint)(local_2c + 0x28);
  _memset(local_2c,0,0x20);
  _memset(local_4c,0,0x20);
  FUN_00538e80(local_2c,local_4c,param_2);
  FUN_00538f50(param_1,local_2c,local_4c);
  __security_check_cookie(local_8 ^ (uint)(local_2c + 0x28));
  return;
}
