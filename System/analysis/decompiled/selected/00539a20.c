void __thiscall FUN_00539a20(int param_1,LPCSTR param_2)

{
  int local_38;
  int local_34;
  int local_30;
  CHAR local_2c [32];
  int local_c;
  undefined4 local_8;

  local_8 = DAT_00c02edc ^ (uint)(local_2c + 0x28);
  local_34 = 0;
  local_c = param_1;
  for (local_30 = 0; local_30 < 7; local_30 = local_30 + 1) {
    for (local_38 = 0; local_38 < *(int *)(&DAT_00b07f10 + local_30 * 4); local_38 = local_38 + 1) {
      FUN_00539ca0(local_2c,local_c + 0x10 + local_34 * 8);
      WritePrivateProfileStringA
                ("WINDOW" + local_30 * 0x20,"INVENTORY" + local_34 * 0x20,local_2c,param_2);
      local_34 = local_34 + 1;
    }
  }
  __security_check_cookie(local_8 ^ (uint)(local_2c + 0x28));
  return;
}
