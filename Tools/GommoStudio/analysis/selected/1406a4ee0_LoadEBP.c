/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/r3.LoadEBP
 * VA: 0x1406a4ee0
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_1400094c0: runtime.mapassign_faststr
 * FUN_140013220: runtime.convT32
 * FUN_140016c60: runtime.newobject
 * FUN_140071a60: runtime.convT64
 * FUN_140072200: runtime.makemap
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_140117060: fmt.Errorf
 * FUN_1406a4ee0: gommo/pkg/assets/r3.LoadEBP
 * FUN_1406a5480: gommo/pkg/assets/r3.(*EBP).parseLumps
 */
undefined1  [24] FUN_1406a4ee0(sdword *param_1,int param_2)

{
  uint uVar1;
  dword dVar2;
  undefined1 auVar3 [24];
  undefined1 auVar4 [24];
  undefined1 auVar5 [24];
  undefined1 auVar6 [24];
  int extraout_RAX;
  int *piVar7;
  uint extraout_RCX;
  uint uVar8;
  undefined8 *puVar9;
  int iVar10;
  int extraout_RBX;
  uint uVar11;
  int iVar12;
  int extraout_RSI;
  int extraout_RSI_00;
  int extraout_R9;
  int extraout_R9_00;
  int *extraout_R11;
  int *extraout_R11_00;
  int unaff_R14;
  undefined1 auVar13 [16];
  sdword *psStack0000000000000008;
  dword adStack_220 [22];
  undefined1 auStack_1c8 [132];
  dword adStack_144 [6];
  dword adStack_12c [35];
  uint uStack_a0;
  uint uStack_98;
  uint uStack_90;
  uint uStack_88;
  uint uStack_80;
  int iStack_78;
  undefined8 uStack_70;
  undefined4 *puStack_68;
  undefined1 auStack_60 [48];
  internal_abi_Type *piStack_30;
  undefined8 uStack_28;
  internal_abi_Type *piStack_20;
  undefined *puStack_18;
  undefined8 *puStack_10;

  psStack0000000000000008 = param_1;
  while (auStack_1c8 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  if (param_2 < 0x184) {
    uStack_28 = FUN_140071a60(param_2);
    piStack_30 = &int___Int_type;
    piStack_20 = &int___Int_type;
    puStack_18 = &DAT_142f46840;
    auVar13 = FUN_140117060("r3: ebp is %d bytes, shorter than its %d-byte header",0x34,&piStack_30,
                            2,2);
    auVar4._16_8_ = 0;
    auVar4._0_16_ = auVar13;
    return auVar4 << 0x40;
  }
  if (*psStack0000000000000008 != 0x14) {
    uStack_28 = FUN_140013220(*psStack0000000000000008);
    piStack_30 = &uint32___Uint32_type;
    piStack_20 = &int___Int_type;
    puStack_18 = &DAT_142f3b598;
    auVar13 = FUN_140117060("r3: ebp version %d, want %d",0x1b,&piStack_30,2,2);
    auVar3._16_8_ = 0;
    auVar3._0_16_ = auVar13;
    return auVar3 << 0x40;
  }
  FUN_14007cc06();
  for (iVar12 = 0; iVar12 < 0x30; iVar12 = iVar12 + 1) {
    dVar2 = *(dword *)(extraout_RAX + 8 + iVar12 * 8);
    adStack_220[iVar12 * 2] = *(dword *)(extraout_RAX + 4 + iVar12 * 8);
    adStack_220[iVar12 * 2 + 1] = dVar2;
  }
  psStack0000000000000008 = (sdword *)extraout_RAX;
  uStack_70 = FUN_140072200(&map_string___uint8___Map_type,0xc,auStack_60);
  iStack_78 = slice_9__14416f910.len;
  uVar8 = 0;
  puVar9 = slice_9__14416f910.array;
  uVar11 = 0x184;
  while( true ) {
    if (iStack_78 <= (int)uVar8) {
      iStack_78 = slice_3__14416f930.len;
      uVar8 = 0;
      puVar9 = slice_3__14416f930.array;
      while( true ) {
        if (iStack_78 <= (int)uVar8) {
          iVar10 = 0;
          for (iVar12 = 0; iVar12 < 0x12; iVar12 = iVar12 + 1) {
            iVar10 = iVar10 + (uint)adStack_220[iVar12 * 2 + 0x13];
          }
          for (iVar12 = 0; iVar12 < 0x12; iVar12 = iVar12 + 1) {
            iVar10 = iVar10 + (uint)adStack_12c[iVar12 * 2];
          }
          if (extraout_RBX != uVar11 + iVar10) {
            uStack_28 = FUN_140071a60(uVar11 + iVar10);
            piStack_30 = &int___Int_type;
            puStack_18 = (undefined *)FUN_140071a60(extraout_RBX);
            piStack_20 = &int___Int_type;
            auVar13 = FUN_140117060("r3: ebp lump sizes sum to %d but the file is %d bytes",0x35,
                                    &piStack_30,2,2);
            auVar6._16_8_ = 0;
            auVar6._0_16_ = auVar13;
            return auVar6 << 0x40;
          }
          puStack_68 = (undefined4 *)FUN_140016c60(&DAT_142868e20);
          *puStack_68 = 0x14;
          auVar13 = FUN_1406a5480(puStack_68,uStack_70);
          if (auVar13._0_8_ == 0) {
            return ZEXT824(puStack_68);
          }
          auVar5._16_8_ = 0;
          auVar5._0_16_ = auVar13;
          return auVar5 << 0x40;
        }
        if (2 < uVar8) {
                    /* WARNING: Subroutine does not return */
          FUN_14007c940(uVar8,uVar11,3);
        }
        uVar1 = adStack_144[uVar8 * 2] + uVar11;
        if (extraout_RCX < uVar1) break;
        if (uVar1 < uVar11) {
                    /* WARNING: Subroutine does not return */
          FUN_14007ca00(uVar11,uVar11,uVar1);
        }
        uStack_a0 = uVar11;
        uStack_98 = uVar8;
        uStack_88 = uVar1;
        uStack_80 = (uint)adStack_144[uVar8 * 2];
        puStack_10 = puVar9;
        piVar7 = (int *)FUN_1400094c0(&map_string___uint8___Map_type,uStack_70,*puVar9,puVar9[1]);
        piVar7[1] = uStack_80;
        piVar7[2] = extraout_RCX - uStack_a0;
        iVar12 = (uStack_a0 & (int)-(extraout_RCX - uStack_a0) >> 0x3f) +
                 (int)psStack0000000000000008;
        if (DAT_1444d6c60 != 0) {
          piVar7 = (int *)FUN_14007c5a0();
          *extraout_R11_00 = extraout_RSI_00;
          extraout_R11_00[1] = extraout_R9_00;
          iVar12 = extraout_RSI_00;
        }
        *piVar7 = iVar12;
        puVar9 = puStack_10 + 3;
        uVar8 = uStack_98 + 1;
        uVar11 = uStack_88;
      }
                    /* WARNING: Subroutine does not return */
      FUN_14007c9c0(uStack_70,uVar11,uVar1);
    }
    if (8 < uVar8) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(uVar8,uVar11,9);
    }
    uVar1 = adStack_220[uVar8 * 2 + 1] + uVar11;
    if (extraout_RCX < uVar1) break;
    if (uVar1 < uVar11) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar11,uVar11,uVar1);
    }
    uStack_a0 = uVar11;
    uStack_90 = uVar8;
    uStack_88 = uVar1;
    uStack_80 = (uint)adStack_220[uVar8 * 2 + 1];
    puStack_10 = puVar9;
    piVar7 = (int *)FUN_1400094c0(&map_string___uint8___Map_type,uStack_70,*puVar9,puVar9[1]);
    piVar7[1] = uStack_80;
    piVar7[2] = extraout_RCX - uStack_a0;
    iVar12 = (uStack_a0 & (int)-(extraout_RCX - uStack_a0) >> 0x3f) + (int)psStack0000000000000008;
    if (DAT_1444d6c60 != 0) {
      piVar7 = (int *)FUN_14007c5a0();
      *extraout_R11 = extraout_RSI;
      extraout_R11[1] = extraout_R9;
      iVar12 = extraout_RSI;
    }
    *piVar7 = iVar12;
    puVar9 = puStack_10 + 3;
    uVar8 = uStack_90 + 1;
    uVar11 = uStack_88;
  }
                    /* WARNING: Subroutine does not return */
  FUN_14007c9c0(uStack_70,uVar11,uVar1);
}
