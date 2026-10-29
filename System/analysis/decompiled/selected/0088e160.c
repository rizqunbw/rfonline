/* Ghidra pseudocode; inferred types/signatures may be incorrect. VA 0x0088e160. */

void FUN_0088e160(char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  FILE *pFVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 uVar9;
  char *pcVar10;
  char *local_644;
  uint local_640;
  int local_63c;
  uint local_638;
  FILE *local_634;
  uint local_630;
  FILE *local_62c [2];
  undefined1 local_624 [4];
  void *local_620;
  undefined4 local_610;
  uint local_60c;
  undefined1 local_608 [4];
  void *local_604;
  undefined4 local_5f4;
  uint local_5f0;
  void *local_5e8;
  undefined4 local_5d8;
  uint local_5d4;
  void *local_5cc;
  undefined4 local_5bc;
  uint local_5b8;
  undefined1 local_5ac [8];
  undefined1 local_5a4 [4];
  void *local_5a0;
  undefined4 local_590;
  uint local_58c;
  uint local_588;
  int local_584;
  char local_580 [4];
  void *local_57c;
  undefined4 local_56c;
  uint local_568;
  uint local_564;
  FILE *local_560;
  char local_548 [56];
  char local_510 [256];
  char local_410 [256];
  char local_310 [256];
  char local_210 [256];
  char local_110 [256];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;

  local_4 = 0xffffffff;
  puStack_8 = &LAB_00aed673;
  local_c = ExceptionList;
  local_10 = DAT_00c02edc ^ (uint)&local_644;
  ExceptionList = &local_c;
  local_644 = param_1;
  local_60c = 0xf;
  local_610 = 0;
  local_620 = (void *)((uint)local_620 & 0xffffff00);
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  FUN_00416940(param_1,(int)pcVar3 - (int)(param_1 + 1));
  local_4 = 0;
  FUN_0088caa0(local_62c,local_624);
  local_4 = 0xffffffff;
  if (0xf < local_60c) {
    _free(local_620);
  }
  if (local_62c[0] == DAT_02788e94) {
    local_60c = 0xf;
    local_610 = 0;
    local_620 = (void *)((uint)local_620 & 0xffffff00);
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_00416940(param_1,(int)pcVar3 - (int)(param_1 + 1));
    local_4 = 1;
    local_58c = 0xf;
    local_590 = 0;
    local_5a0 = (void *)((uint)local_5a0 & 0xffffff00);
    FUN_004166a0(local_624,0,0xffffffff);
    local_588 = 1;
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_0088de80(local_62c,local_5a4);
    if (0xf < local_58c) {
      _free(local_5a0);
    }
    local_58c = 0xf;
    local_590 = 0;
    local_5a0 = (void *)((uint)local_5a0 & 0xffffff00);
    local_4 = 0xffffffff;
    if (0xf < local_60c) {
      _free(local_620);
    }
    _sprintf(local_410,"%sRFSINFO.DAT",param_1);
    local_634 = _fopen(local_410,"rb");
    if (local_634 == (FILE *)0x0) {
      local_63c = 0;
      while( true ) {
        iVar4 = local_63c;
        _sprintf(local_210,"DATA%d.RFS",local_63c);
        _sprintf(local_410,"%sDATA%d.RFS",param_1,iVar4);
        local_62c[0] = _fopen(local_410,"rb");
        if (local_62c[0] == (FILE *)0x0) break;
        local_640 = 0;
        local_630 = 0;
        local_634 = (FILE *)0x0;
        local_568 = 0xf;
        local_56c = 0;
        local_57c = (void *)((uint)local_57c & 0xffffff00);
        local_4 = 6;
        FUN_007b30a1(&local_640,1,4,local_62c[0]);
        local_638 = 0;
        if (local_640 != 0) {
          do {
            pFVar5 = local_62c[0];
            FUN_007b30a1(local_548,1,0x38,local_62c[0]);
            FUN_007b30a1(&local_630,1,4,pFVar5);
            FUN_007b30a1(&local_634,1,4,pFVar5);
            pcVar3 = local_644;
            pcVar6 = local_644;
            do {
              cVar1 = *pcVar6;
              pcVar6 = pcVar6 + 1;
            } while (cVar1 != '\0');
            pcVar7 = local_548;
            do {
              cVar1 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            pcVar8 = local_644;
            do {
              cVar1 = *pcVar8;
              pcVar8 = pcVar8 + 1;
            } while (cVar1 != '\0');
            pcVar10 = local_210;
            do {
              cVar1 = *pcVar10;
              pcVar10 = pcVar10 + 1;
            } while (cVar1 != '\0');
            if ((pcVar6 + (int)(pcVar7 + (-(int)(local_548 + 1) - (int)(local_644 + 1))) <
                 (char *)0x100) &&
               (pcVar8 + (int)(pcVar10 + (-(int)(local_210 + 1) - (int)(local_644 + 1))) <
                (char *)0x100)) {
              _sprintf(local_510,"%s%s",local_644,local_548);
              _sprintf(local_310,"%s%s",pcVar3,local_210);
              uVar2 = local_630;
              pFVar5 = local_634;
              pcVar3 = local_310;
              do {
                cVar1 = *pcVar3;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
              FUN_00416940(local_310,(int)pcVar3 - (int)(local_310 + 1));
              local_564 = uVar2;
              local_560 = pFVar5;
              __strupr(local_510);
              pcVar3 = local_510;
              do {
                cVar1 = *pcVar3;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
              pcVar3 = local_510;
              local_5f0 = 0xf;
              local_5f4 = 0;
              local_604 = (void *)((uint)local_604 & 0xffffff00);
              do {
                cVar1 = *pcVar3;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
              FUN_00416940(local_510,(int)pcVar3 - (int)(local_510 + 1));
              local_4._0_1_ = 7;
              uVar9 = FUN_0088cd50(local_608,local_580);
              local_4 = CONCAT31(local_4._1_3_,8);
              FUN_0088dfc0(local_5ac,uVar9);
              if (0xf < local_5b8) {
                _free(local_5cc);
              }
              local_5b8 = 0xf;
              local_5bc = 0;
              local_5cc = (void *)((uint)local_5cc & 0xffffff00);
              if (0xf < local_5d4) {
                _free(local_5e8);
              }
              local_5d4 = 0xf;
              local_5d8 = 0;
              local_5e8 = (void *)((uint)local_5e8 & 0xffffff00);
              local_4 = CONCAT31(local_4._1_3_,6);
              if (0xf < local_5f0) {
                _free(local_604);
              }
            }
            else {
              FUN_0088fea0(&DAT_0278f800,"ReadRFSHeader:%s:%s:%s",local_548,local_210,local_644);
            }
            local_638 = local_638 + 1;
          } while (local_638 < local_640);
        }
        _fclose(local_62c[0]);
        local_4 = 0xffffffff;
        if (0xf < local_568) {
          _free(local_57c);
        }
        local_63c = local_63c + 1;
        if (0x3ff < local_63c) break;
        param_1 = local_644;
      }
    }
    else {
      iVar4 = FUN_007b7a76(local_634,&DAT_00b010e4,local_310);
      while (iVar4 != -1) {
        _sprintf(local_410,"%s%s",local_644,local_310);
        pFVar5 = _fopen(local_410,"rb");
        if (pFVar5 != (FILE *)0x0) {
          local_640 = 0;
          local_638 = 0;
          local_63c = 0;
          local_58c = 0xf;
          local_590 = 0;
          local_5a0 = (void *)((uint)local_5a0 & 0xffffff00);
          local_4 = 3;
          FUN_007b30a1(&local_640,1,4,pFVar5);
          local_630 = 0;
          if (local_640 != 0) {
            do {
              FUN_007b30a1(local_580,1,0x38,pFVar5);
              FUN_007b30a1(&local_638,1,4,pFVar5);
              FUN_007b30a1(&local_63c,1,4,pFVar5);
              pcVar3 = local_644;
              do {
                cVar1 = *pcVar3;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
              pcVar6 = local_580;
              do {
                cVar1 = *pcVar6;
                pcVar6 = pcVar6 + 1;
              } while (cVar1 != '\0');
              pcVar7 = local_644;
              do {
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
              } while (cVar1 != '\0');
              pcVar8 = local_410;
              do {
                cVar1 = *pcVar8;
                pcVar8 = pcVar8 + 1;
              } while (cVar1 != '\0');
              if ((pcVar3 + (int)(pcVar6 + (-(int)(local_580 + 1) - (int)(local_644 + 1))) <
                   (char *)0x100) &&
                 (pcVar7 + (int)(pcVar8 + (-(int)(local_410 + 1) - (int)(local_644 + 1))) <
                  (char *)0x100)) {
                _sprintf(local_510,"%s%s",local_644,local_580);
                _sprintf(local_110,"%s",local_410);
                uVar2 = local_638;
                iVar4 = local_63c;
                pcVar3 = local_110;
                do {
                  cVar1 = *pcVar3;
                  pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                FUN_00416940(local_110,(int)pcVar3 - (int)(local_110 + 1));
                local_588 = uVar2;
                local_584 = iVar4;
                __strupr(local_510);
                pcVar3 = local_510;
                do {
                  cVar1 = *pcVar3;
                  pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                pcVar3 = local_510;
                local_60c = 0xf;
                local_610 = 0;
                local_620 = (void *)((uint)local_620 & 0xffffff00);
                do {
                  cVar1 = *pcVar3;
                  pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                FUN_00416940(local_510,(int)pcVar3 - (int)(local_510 + 1));
                local_4._0_1_ = 4;
                uVar9 = FUN_0088cd50(local_624,local_5a4);
                local_4._0_1_ = 5;
                FUN_0088dfc0(local_62c,uVar9);
                FUN_0088c930();
                local_4 = CONCAT31(local_4._1_3_,3);
                if (0xf < local_60c) {
                  _free(local_620);
                }
              }
              else {
                FUN_0088fea0(&DAT_0278f800,"ReadRFSHeader:%s:%s:%s",local_580,local_410,local_644);
              }
              local_630 = local_630 + 1;
            } while (local_630 < local_640);
          }
          _fclose(pFVar5);
          local_4 = 0xffffffff;
          if (0xf < local_58c) {
            _free(local_5a0);
          }
        }
        iVar4 = FUN_007b7a76(local_634,&DAT_00b010e4,local_310);
      }
      _fclose(local_634);
    }
  }
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_644);
  return;
}
