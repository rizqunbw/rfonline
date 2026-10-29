/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x00539d80. */

void FUN_00539d80(char *param_1,int param_2)

{
  int local_c;

  local_c = 0;
  while( true ) {
    if (0x55 < local_c) {
      _sprintf(param_1,"?");
      return;
    }
    if (param_2 == *(int *)(&DAT_00b07138 + local_c * 4)) break;
    local_c = local_c + 1;
  }
  _sprintf(param_1,&DAT_00b06d30 + local_c * 0xc);
  return;
}
