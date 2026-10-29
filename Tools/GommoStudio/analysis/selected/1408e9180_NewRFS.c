/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/rfpack.NewRFS
 * VA: 0x1408e9180
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140009200: runtime.mapaccess2_faststr
 * FUN_1400094c0: runtime.mapassign_faststr
 * FUN_140016c60: runtime.newobject
 * FUN_140071a60: runtime.convT64
 * FUN_140071ae0: runtime.convTstring
 * FUN_140072200: runtime.makemap
 * FUN_1400762e0: runtime.makeslice
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c5c0: runtime.gcWriteBarrier3
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_140117060: fmt.Errorf
 * FUN_14032aa40: gommo/pkg/assets/vfs.Clean
 * FUN_1408e9180: gommo/pkg/assets/rfpack.NewRFS
 * FUN_1408e9d80: gommo/pkg/assets/rfpack.cstring
 */
undefined1  [24]
FUN_1408e9180(int param_1,undefined8 param_2,int param_3,undefined8 param_4,undefined8 param_5)

{
  undefined1 auVar1 [24];
  undefined1 auVar2 [24];
  undefined1 auVar3 [24];
  undefined1 auVar4 [24];
  undefined8 *puVar5;
  undefined8 extraout_RAX;
  undefined8 extraout_RCX;
  uint uVar6;
  undefined8 extraout_RCX_00;
  undefined8 extraout_RCX_01;
  char extraout_BL;
  int extraout_RBX;
  uint uVar7;
  int extraout_RBX_00;
  int iVar8;
  uint uVar9;
  undefined8 extraout_RBX_01;
  undefined8 extraout_RSI;
  int extraout_RSI_00;
  undefined8 extraout_RDI;
  undefined8 extraout_R8;
  int extraout_R8_00;
  undefined8 extraout_R9;
  undefined8 uVar10;
  uint uVar11;
  int iVar12;
  undefined8 *extraout_R11;
  undefined8 *extraout_R11_00;
  undefined8 *extraout_R11_01;
  undefined8 *extraout_R11_02;
  int unaff_R14;
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  int iStack0000000000000008;
  undefined8 uStack0000000000000010;
  int iStack0000000000000018;
  undefined8 uStack0000000000000020;
  undefined8 uStack0000000000000028;
  uint uStack_100;
  int iStack_f8;
  int iStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 *puStack_c8;
  int iStack_c0;
  internal_abi_Type *piStack_b8;
  undefined8 uStack_b0;
  internal_abi_Type *piStack_a8;
  undefined8 uStack_a0;
  internal_abi_Type *piStack_98;
  undefined8 uStack_90;
  internal_abi_Type *piStack_88;
  undefined8 uStack_80;
  internal_abi_Type *piStack_78;
  undefined8 uStack_70;
  internal_abi_Type *piStack_68;
  undefined8 uStack_60;
  internal_abi_Type *piStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  internal_abi_Type *piStack_38;
  undefined8 uStack_30;
  internal_abi_Type *piStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  dword *pdStack_10;

  iStack0000000000000008 = param_1;
  iStack0000000000000018 = param_3;
  uStack0000000000000010 = param_2;
  uStack0000000000000028 = param_5;
  uStack0000000000000020 = param_4;
  while (&uStack_100 <= *(uint **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  pdStack_10 = (dword *)FUN_140016c60(&_4_uint8___Array_type);
  (**(code **)(iStack0000000000000008 + 0x18))(uStack0000000000000010,pdStack_10,4,4,0);
  if (extraout_RBX != 0) {
    uStack_d8 = extraout_RCX;
    uStack_30 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_38 = &string___String_type;
    if (extraout_RBX == 0) {
      piStack_28 = (internal_abi_Type *)0x0;
    }
    else {
      piStack_28 = *(internal_abi_Type **)(extraout_RBX + 8);
    }
    uStack_20 = uStack_d8;
    auVar13 = FUN_140117060("rfs %s: read count: %w",0x16,&piStack_38,2,2);
    auVar3._16_8_ = 0;
    auVar3._0_16_ = auVar13;
    return auVar3 << 0x40;
  }
  uVar6 = (uint)*pdStack_10;
  if (0x400000 < uVar6) {
    uStack_30 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_38 = &string___String_type;
    uStack_20 = FUN_140071a60(uVar6);
    piStack_28 = &int64___Int64_type;
    auVar13 = FUN_140117060("rfs %s: implausible entry count %d",0x22,&piStack_38,2,2);
    auVar2._16_8_ = 0;
    auVar2._0_16_ = auVar13;
    return auVar2 << 0x40;
  }
  uVar7 = uVar6 * 0x40;
  iStack_c0 = FUN_1400762e0(&uint8___Uint8_type,uVar7,uVar7);
  (**(code **)(iStack0000000000000008 + 0x18))(uStack0000000000000010,iStack_c0,uVar7,uVar7,4);
  if (extraout_RBX_00 != 0) {
    uStack_e0 = extraout_RCX_00;
    uStack_60 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_68 = &string___String_type;
    uStack_50 = FUN_140071a60(uVar6);
    piStack_58 = &int64___Int64_type;
    if (extraout_RBX_00 == 0) {
      uStack_48 = 0;
    }
    else {
      uStack_48 = *(undefined8 *)(extraout_RBX_00 + 8);
    }
    uStack_40 = uStack_e0;
    auVar13 = FUN_140117060("rfs %s: read directory of %d: %w",0x20,&piStack_68,3,3);
    auVar1._16_8_ = 0;
    auVar1._0_16_ = auVar13;
    return auVar1 << 0x40;
  }
  uStack_18 = FUN_140072200(&DAT_142568b60,uVar6,0);
  puVar5 = (undefined8 *)FUN_140016c60(&DAT_142782ee0);
  puVar5[1] = uStack0000000000000028;
  if (DAT_1444d6c60 != 0) {
    puVar5 = (undefined8 *)FUN_14007c5c0();
    *extraout_R11 = uStack0000000000000020;
    extraout_R11[1] = uStack0000000000000010;
    extraout_R11[2] = uStack_18;
  }
  *puVar5 = uStack0000000000000020;
  puVar5[3] = iStack0000000000000008;
  puVar5[4] = uStack0000000000000010;
  puVar5[7] = uStack_18;
  iVar8 = 0;
  puStack_c8 = puVar5;
  do {
    if ((int)uVar6 <= iVar8) {
      return ZEXT824(puVar5);
    }
    uVar9 = iVar8 * 0x40;
    if (uVar7 < uVar9) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar9);
    }
    uVar11 = uVar7 + iVar8 * -0x40;
    iVar12 = ((int)-uVar11 >> 0x3f & uVar9) + iStack_c0;
    if (uVar11 < 0x38) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c9c0(puVar5,uVar9,0x38);
    }
    uStack_100 = uVar11;
    iStack_f8 = iVar8;
    iStack_f0 = iVar12;
    auVar13 = FUN_1408e9d80(iVar12,0x38,uVar11);
    if (auVar13._8_8_ == 0) {
      puVar5 = puStack_c8;
    }
    else {
      uStack_e8 = auVar13._0_8_;
      auVar14 = FUN_14032aa40();
      uVar10 = auVar14._8_8_;
      if (uStack_100 < 0x38) {
                    /* WARNING: Subroutine does not return */
        FUN_14007ca00(0x38);
      }
      uVar9 = uStack_100 - 0x38;
      if (uVar9 < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940(3,uVar10,uVar9);
      }
      uVar9 = (uint)*(dword *)((uint)((dword)((int)-uVar9 >> 0x3f) & 0x38) + iStack_f0);
      if (uStack_100 < 0x3c) {
                    /* WARNING: Subroutine does not return */
        FUN_14007ca00(0x3c);
      }
      if (uStack_100 - 0x3c < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940(3);
      }
      uVar11 = (uint)*(dword *)((uint)((dword)((int)-(uStack_100 - 0x3c) >> 0x3f) & 0x3c) +
                               iStack_f0);
      if (iStack0000000000000018 < (int)(uVar9 + uVar11)) {
        FUN_14007cc70();
        uStack_b0 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
        piStack_b8 = &string___String_type;
        uStack_a0 = FUN_140071ae0(uStack_e8,auVar13._8_8_);
        piStack_a8 = &string___String_type;
        uStack_90 = FUN_140071a60(uVar9);
        piStack_98 = &int64___Int64_type;
        uStack_80 = FUN_140071a60(uVar11);
        piStack_88 = &int64___Int64_type;
        uStack_70 = FUN_140071a60(iStack0000000000000018);
        piStack_78 = &int64___Int64_type;
        auVar13 = FUN_140117060("rfs %s: entry %q at %d+%d exceeds archive size %d",0x31,&piStack_b8
                                ,5,5);
        auVar4._16_8_ = 0;
        auVar4._0_16_ = auVar13;
        return auVar4 << 0x40;
      }
      uStack_d0 = auVar14._0_8_;
      FUN_140009200(&DAT_142568b60,puStack_c8[7],auVar14._0_8_,uVar10);
      if (extraout_BL == '\0') {
        puVar5 = (undefined8 *)FUN_1400094c0(&DAT_142568b60,puStack_c8[7],uStack_d0,uVar10);
        puVar5[1] = uVar10;
        puVar5[2] = uVar9;
        puVar5[3] = uVar11;
        if (DAT_1444d6c60 != 0) {
          puVar5 = (undefined8 *)FUN_14007c5a0();
          *extraout_R11_00 = uStack_d0;
          extraout_R11_00[1] = extraout_R8;
        }
        *puVar5 = uStack_d0;
        uVar9 = puStack_c8[9] + 1;
        auVar13._8_8_ = uVar9;
        auVar13._0_8_ = puStack_c8[8];
        if ((uint)puStack_c8[10] < uVar9) {
          FUN_1400763c0(puStack_c8[8],uVar9,puStack_c8[10],1,&string___String_type);
          puVar5 = puStack_c8;
          auVar13._8_8_ = extraout_RBX_01;
          auVar13._0_8_ = extraout_RAX;
          puStack_c8[10] = extraout_RCX_01;
          if (DAT_1444d6c60 != 0) {
            auVar13 = FUN_14007c5a0();
            *extraout_R11_01 = auVar13._0_8_;
            extraout_R11_01[1] = extraout_RSI;
          }
          puVar5[8] = auVar13._0_8_;
        }
        iVar12 = auVar13._0_8_;
        puStack_c8[9] = auVar13._8_8_;
        iVar8 = (auVar13._8_8_ + -1) * 0x10;
        *(undefined8 *)(iVar12 + 8 + iVar8) = uVar10;
        puVar5 = puStack_c8;
        uVar10 = uStack_d0;
        if (DAT_1444d6c60 != 0) {
          puVar5 = (undefined8 *)FUN_14007c5a0();
          *extraout_R11_02 = extraout_R9;
          extraout_R11_02[1] = extraout_RDI;
          iVar8 = extraout_RSI_00;
          iVar12 = extraout_R8_00;
          uVar10 = extraout_R9;
        }
        *(undefined8 *)(iVar12 + iVar8) = uVar10;
      }
      else {
        puVar5 = puStack_c8;
      }
    }
    iVar8 = iStack_f8 + 1;
  } while( true );
}
