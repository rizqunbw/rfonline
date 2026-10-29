/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x00538e80. */

void FUN_00538e80(undefined4 param_1,undefined4 param_2,char *param_3)

{
  size_t sVar1;
  int local_34;
  uint local_30;
  char local_2c [36];
  undefined4 local_8;

  local_8 = DAT_00c02edc ^ (uint)(local_2c + 0x28);
  _memset(local_2c,0,0x20);
  local_30 = 0;
  local_34 = 0;
  while( true ) {
    sVar1 = _strlen(param_3);
    if (sVar1 <= local_30) break;
    if (param_3[local_30] == '+') {
      FUN_005b0d60(param_1,local_2c,0x20);
      _memset(local_2c,0,0x20);
      local_34 = 0;
    }
    else {
      local_2c[local_34] = param_3[local_30];
      local_34 = local_34 + 1;
    }
    local_30 = local_30 + 1;
  }
  FUN_005b0d60(param_2,local_2c,0x20);
  __security_check_cookie(local_8 ^ (uint)(local_2c + 0x28));
  return;
}
