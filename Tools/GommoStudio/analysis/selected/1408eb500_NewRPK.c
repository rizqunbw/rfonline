/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/rfpack.NewRPK
 * VA: 0x1408eb500
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140009200: runtime.mapaccess2_faststr
 * FUN_1400094c0: runtime.mapassign_faststr
 * FUN_140013220: runtime.convT32
 * FUN_140016c60: runtime.newobject
 * FUN_140017560: runtime.wbMove
 * FUN_140071a60: runtime.convT64
 * FUN_140071ae0: runtime.convTstring
 * FUN_140071b80: runtime.convTslice
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
 * FUN_14015c820: sort.Slice
 * FUN_1408e9d80: gommo/pkg/assets/rfpack.cstring
 * FUN_1408eb500: gommo/pkg/assets/rfpack.NewRPK
 * FUN_1408ec200: gommo/pkg/assets/rfpack.NewRPK.sortEntries.func1
 * FUN_1408ec260: gommo/pkg/assets/rfpack.walkRPK
 */
undefined1  [24]
FUN_1408eb500(int param_1,undefined8 param_2,int param_3,undefined8 param_4,undefined8 param_5)

{
  float fVar1;
  sdword sVar2;
  int iVar3;
  undefined1 auVar4 [24];
  undefined1 auVar5 [24];
  undefined1 auVar6 [24];
  undefined1 auVar7 [24];
  undefined1 auVar8 [24];
  undefined1 auVar9 [24];
  undefined1 auVar10 [24];
  uint uVar11;
  int extraout_RAX;
  undefined8 uVar12;
  undefined8 *puVar13;
  undefined8 extraout_RAX_00;
  undefined8 extraout_RCX;
  undefined8 extraout_RCX_00;
  undefined8 extraout_RCX_01;
  undefined8 extraout_RCX_02;
  uint uVar14;
  char extraout_BL;
  int extraout_RBX;
  int extraout_RBX_00;
  undefined1 (*pauVar15) [16];
  int extraout_RBX_01;
  undefined8 extraout_RBX_02;
  undefined8 extraout_RSI;
  int iVar16;
  undefined8 extraout_RSI_00;
  int extraout_RSI_01;
  int extraout_RDI;
  undefined8 extraout_R8;
  int iVar17;
  int extraout_R9;
  undefined8 extraout_R10;
  undefined8 *extraout_R11;
  undefined8 *extraout_R11_00;
  undefined8 *extraout_R11_01;
  undefined8 *extraout_R11_02;
  uint uVar18;
  int iVar19;
  uint uVar20;
  int unaff_R14;
  uint uVar21;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar22 [16];
  int iStack0000000000000008;
  undefined8 uStack0000000000000010;
  int iStack0000000000000018;
  undefined8 uStack0000000000000020;
  undefined8 uStack0000000000000028;
  uint uStack_150;
  int iStack_148;
  undefined8 uStack_140;
  int iStack_138;
  uint uStack_130;
  uint uStack_128;
  uint uStack_120;
  uint uStack_118;
  int iStack_110;
  int iStack_108;
  int iStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  int iStack_e8;
  undefined8 *puStack_e0;
  undefined1 auStack_d8 [16];
  undefined8 uStack_c8;
  uint uStack_c0;
  uint uStack_b8;
  undefined8 uStack_b0;
  code *pcStack_a8;
  int iStack_a0;
  int iStack_98;
  undefined8 uStack_90;
  internal_abi_Type *piStack_88;
  undefined8 uStack_80;
  internal_abi_Type *piStack_78;
  undefined8 uStack_70;
  internal_abi_Type *piStack_68;
  undefined8 uStack_60;
  internal_abi_Type *piStack_58;
  undefined8 uStack_50;
  internal_abi_Type *piStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined1 (*pauStack_28) [16];
  int iStack_20;
  int iStack_18;
  float *pfStack_10;

  iStack0000000000000008 = param_1;
  iStack0000000000000018 = param_3;
  uStack0000000000000010 = param_2;
  uStack0000000000000028 = param_5;
  uStack0000000000000020 = param_4;
  while (&uStack_150 <= *(uint **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  pfStack_10 = (float *)FUN_140016c60(&_8_uint8___Array_type);
  (**(code **)(iStack0000000000000008 + 0x18))(uStack0000000000000010,pfStack_10,8,8,0);
  if (extraout_RBX != 0) {
    uStack_f0 = extraout_RCX;
    uStack_50 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_58 = &string___String_type;
    if (extraout_RBX == 0) {
      piStack_48 = (internal_abi_Type *)0x0;
    }
    else {
      piStack_48 = *(internal_abi_Type **)(extraout_RBX + 8);
    }
    uStack_40 = uStack_f0;
    auVar22 = FUN_140117060("rpk %s: read header: %w",0x17,&piStack_58,2,2);
    auVar8._16_8_ = 0;
    auVar8._0_16_ = auVar22;
    return auVar8 << 0x40;
  }
  fVar1 = *pfStack_10;
  if ((fVar1 != 1.0) || (NAN(fVar1))) {
    uStack_50 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_58 = &string___String_type;
    uStack_40 = FUN_140013220(fVar1);
    piStack_48 = &float32___Float32_type;
    auVar22 = FUN_140117060("rpk %s: version %g, want 1.0",0x1c,&piStack_58,2,2);
    auVar7._16_8_ = 0;
    auVar7._0_16_ = auVar22;
    return auVar7 << 0x40;
  }
  uVar14 = (uint)(dword)pfStack_10[1];
  uStack_118 = uVar14;
  if (0x3fffff < uVar14 - 1) {
    uStack_50 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_58 = &string___String_type;
    uStack_40 = FUN_140071a60(uStack_118);
    piStack_48 = &int___Int_type;
    auVar22 = FUN_140117060("rpk %s: implausible record count %d",0x23,&piStack_58,2,2);
    auVar6._16_8_ = 0;
    auVar6._0_16_ = auVar22;
    return auVar6 << 0x40;
  }
  uStack_120 = uVar14 * 0x48;
  if (iStack0000000000000018 < (int)(uVar14 * 0x48 + 8)) {
    uStack_80 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_88 = &string___String_type;
    uStack_70 = FUN_140071a60(uStack_118);
    piStack_78 = &int___Int_type;
    uStack_60 = FUN_140071a60(iStack0000000000000018);
    piStack_68 = &int64___Int64_type;
    auVar22 = FUN_140117060("rpk %s: %d records do not fit in %d bytes",0x29,&piStack_88,3,3);
    auVar5._16_8_ = 0;
    auVar5._0_16_ = auVar22;
    return auVar5 << 0x40;
  }
  iStack_18 = FUN_1400762e0(&uint8___Uint8_type,uStack_120);
  (**(code **)(iStack0000000000000008 + 0x18))
            (uStack0000000000000010,iStack_18,uStack_120,uStack_120,8);
  uVar18 = uStack_118;
  if (extraout_RBX_00 != 0) {
    uStack_f8 = extraout_RCX_00;
    uStack_50 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
    piStack_58 = &string___String_type;
    if (extraout_RBX_00 == 0) {
      piStack_48 = (internal_abi_Type *)0x0;
    }
    else {
      piStack_48 = *(internal_abi_Type **)(extraout_RBX_00 + 8);
    }
    uStack_40 = uStack_f8;
    auVar22 = FUN_140117060("rpk %s: read tables: %w",0x17,&piStack_58,2,2);
    auVar4._16_8_ = 0;
    auVar4._0_16_ = auVar22;
    return auVar4 << 0x40;
  }
  uVar11 = uStack_118 * 4;
  if (uStack_120 < uVar11) {
                    /* WARNING: Subroutine does not return */
    FUN_14007c9c0(uVar11,0,uVar11);
  }
  uStack_128 = uStack_118 << 3;
  if (uStack_120 < uStack_128) {
                    /* WARNING: Subroutine does not return */
    FUN_14007c9c0();
  }
  if (uStack_128 < uVar11) {
                    /* WARNING: Subroutine does not return */
    FUN_14007ca00();
  }
  iStack_20 = FUN_1400762e0(&gommo/pkg/assets/rfpack::
                             gommo_pkg_assets_rfpack_rpkRecord___Struct_type,uStack_118,uStack_118);
  iStack_148 = uStack_120 + uVar18 * -4;
  uStack_150 = uStack_128 + uVar18 * -4;
  iStack_e8 = (-iStack_148 >> 0x3f & uVar11) + iStack_18;
  iStack_110 = ((int)(uVar14 * -0x40) >> 0x3f & uStack_128) + iStack_18;
  iVar17 = 0;
  while( true ) {
    if ((int)uStack_118 <= iVar17) {
      uStack_30 = FUN_140072200(&DAT_142568b60,uStack_118,0,uStack_120,uVar11);
      puStack_e0 = (undefined8 *)FUN_140016c60(&DAT_142782fe0);
      puStack_e0[1] = uStack0000000000000028;
      if (DAT_1444d6c60 != 0) {
        puStack_e0 = (undefined8 *)FUN_14007c5c0();
        *extraout_R11 = uStack0000000000000020;
        extraout_R11[1] = uStack0000000000000010;
        extraout_R11[2] = uStack_30;
      }
      *puStack_e0 = uStack0000000000000020;
      puStack_e0[3] = iStack0000000000000008;
      puStack_e0[4] = uStack0000000000000010;
      puStack_e0[7] = uStack_30;
      FUN_1408ec260(iStack_20,uStack_118,uStack_118,iStack_18,uVar11,uStack_120);
      if (extraout_RDI != 0) {
        auVar9._8_8_ = extraout_RSI;
        auVar9._0_8_ = extraout_RDI;
        auVar9._16_8_ = 0;
        return auVar9 << 0x40;
      }
      iStack_100 = extraout_RAX;
      uVar12 = FUN_140071b80();
      pcStack_a8 = FUN_1408ec200;
      iStack_a0 = iStack_100;
      iStack_98 = extraout_RBX_01;
      uStack_90 = extraout_RCX_01;
      FUN_14015c820(&DAT_14244c020,uVar12,&pcStack_a8);
      iVar17 = iStack_100;
      uStack_118 = 0;
      while( true ) {
        if (extraout_RBX_01 <= (int)uStack_118) {
          return ZEXT824(puStack_e0);
        }
        iVar19 = uStack_118 + 1;
        iVar16 = (iStack0000000000000018 - uStack_120) + -8;
        if (iVar19 < extraout_RBX_01) {
          iVar16 = *(int *)(iVar17 + 0x10 + iVar19 * 0x20);
        }
        uStack_118 = uStack_118 * 0x20;
        iVar16 = iVar16 - *(int *)(iVar17 + 0x10 + uStack_118);
        *(int *)(iVar17 + 0x18 + uStack_118) = iVar16;
        iVar3 = *(int *)(iVar17 + 0x10 + uStack_118);
        *(uint *)(iVar17 + 0x10 + uStack_118) = uStack_120 + iVar3 + 8;
        if ((iVar16 < 0) || (iStack0000000000000018 < (int)(iVar16 + iVar3 + uStack_120 + 8)))
        break;
        uStack_130 = iVar19;
        FUN_140009200(&DAT_142568b60,puStack_e0[7],*(undefined8 *)(iVar17 + uStack_118),
                      *(undefined8 *)(iVar17 + 8 + uStack_118));
        if (extraout_BL == '\0') {
          uStack_38 = *(undefined8 *)(iStack_100 + uStack_118);
          iStack_138 = *(int *)(iStack_100 + 8 + uStack_118);
          uStack_128 = *(uint *)(iStack_100 + 0x18 + uStack_118);
          uStack_140 = *(undefined8 *)(iStack_100 + 0x10 + uStack_118);
          puVar13 = (undefined8 *)FUN_1400094c0(&DAT_142568b60,puStack_e0[7]);
          puVar13[1] = iStack_138;
          puVar13[2] = uStack_140;
          puVar13[3] = uStack_128;
          if (DAT_1444d6c60 != 0) {
            uVar12 = *puVar13;
            puVar13 = (undefined8 *)FUN_14007c5a0();
            *extraout_R11_00 = uStack_38;
            extraout_R11_00[1] = uVar12;
          }
          *puVar13 = uStack_38;
          uVar18 = puStack_e0[9] + 1;
          auVar22._8_8_ = uVar18;
          auVar22._0_8_ = puStack_e0[8];
          puVar13 = (undefined8 *)(iStack_100 + uStack_118);
          uVar14 = *(int *)(iStack_100 + 8 + uStack_118);
          uVar12 = *puVar13;
          if ((uint)puStack_e0[10] < uVar18) {
            uStack_118 = uVar14;
            uStack_38 = *puVar13;
            FUN_1400763c0(puStack_e0[8],uVar18,puStack_e0[10],1,&string___String_type);
            puVar13 = puStack_e0;
            auVar22._8_8_ = extraout_RBX_02;
            auVar22._0_8_ = extraout_RAX_00;
            puStack_e0[10] = extraout_RCX_02;
            if (DAT_1444d6c60 != 0) {
              auVar22 = FUN_14007c5a0();
              *extraout_R11_01 = auVar22._0_8_;
              extraout_R11_01[1] = extraout_RSI_00;
            }
            puVar13[8] = auVar22._0_8_;
            uVar14 = uStack_118;
            uVar12 = uStack_38;
          }
          puStack_e0[9] = auVar22._8_8_;
          iVar19 = (auVar22._8_8_ + -1) * 0x10;
          *(uint *)(auVar22._0_8_ + 8 + iVar19) = uVar14;
          iVar17 = iStack_100;
          if (DAT_1444d6c60 != 0) {
            FUN_14007c5a0();
            *extraout_R11_02 = extraout_R10;
            extraout_R11_02[1] = extraout_R8;
            iVar19 = extraout_RSI_01;
            iVar17 = extraout_R9;
            uVar12 = extraout_R10;
          }
          *(undefined8 *)(auVar22._0_8_ + iVar19) = uVar12;
        }
        else {
          iVar17 = iStack_100;
        }
        uStack_118 = uStack_130;
      }
      uStack_50 = FUN_140071ae0(uStack0000000000000020,uStack0000000000000028);
      piStack_58 = &string___String_type;
      uStack_40 = FUN_140071ae0(*(undefined8 *)(iStack_100 + uStack_118),
                                *(undefined8 *)(iStack_100 + 8 + uStack_118));
      piStack_48 = &string___String_type;
      auVar22 = FUN_140117060("rpk %s: %q spans past the archive",0x21,&piStack_58,2,2);
      auVar10._16_8_ = 0;
      auVar10._0_16_ = auVar22;
      return auVar10 << 0x40;
    }
    uVar18 = iVar17 * 0x40;
    if (uVar14 * 0x40 < uVar18) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar18);
    }
    uVar21 = uVar14 * 0x40 + iVar17 * -0x40;
    uVar20 = iVar17 * 4;
    iVar19 = (uVar18 & (int)-uVar21 >> 0x3f) + iStack_110;
    if (uStack_150 < uVar20) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar20,uStack_118,uStack_150);
    }
    uVar18 = uStack_150 + iVar17 * -4;
    uStack_130 = uVar20;
    if (uVar18 < 4) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(3,uStack_118,uVar18);
    }
    sVar2 = *(sdword *)(iStack_e8 + ((int)(uVar20 - iStack_148) >> 0x3f & uVar20));
    if (uVar21 < 0x34) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c9c0(iStack_20,uStack_118,0x34);
    }
    uStack_130 = iVar17;
    iStack_108 = iVar19;
    auVar22 = FUN_1408e9d80(iVar19,0x34,uVar21);
    if (uVar21 < 0x3a) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(0x3a);
    }
    uVar18 = uVar21 - 0x3a;
    if (uVar18 < 2) break;
    uVar18 = (uint)*(ushort *)(iStack_108 + (uint)((dword)((int)-uVar18 >> 0x3f) & 0x3a));
    if (uVar21 < 0x3c) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(0x3c);
    }
    if (uVar21 - 0x3c < 4) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(3);
    }
    iVar17 = uStack_130 * 0x30;
    uStack_b8 = (uint)*(dword *)(iStack_108 + (uint)((dword)((int)-(uVar21 - 0x3c) >> 0x3f) & 0x3c))
    ;
    uStack_c8 = CONCAT44((sdword)((uint)in_XMM15_Qa >> 0x20),sVar2);
    pauVar15 = (undefined1 (*) [16])(iStack_20 + iVar17);
    uStack_b0 = CONCAT71((int7)((uint)in_XMM15_Qb >> 8),sVar2 == -1);
    uStack_c0 = uVar18;
    auStack_d8 = auVar22;
    if (DAT_1444d6c60 != 0) {
      iStack_138 = iVar17;
      pauStack_28 = pauVar15;
      FUN_140017560(&gommo/pkg/assets/rfpack::gommo_pkg_assets_rfpack_rpkRecord___Struct_type,
                    pauVar15,auStack_d8);
      pauVar15 = pauStack_28;
      iVar17 = iStack_138;
    }
    iVar17 = iStack_20 + iVar17;
    *pauVar15 = auStack_d8;
    *(undefined8 *)(iVar17 + 0x10) = uStack_c8;
    *(uint *)(iVar17 + 0x18) = uStack_c0;
    *(uint *)(iVar17 + 0x20) = uStack_b8;
    *(undefined8 *)(iVar17 + 0x28) = uStack_b0;
    iVar17 = uStack_130 + 1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_14007c940(1,auVar22._8_8_,uVar18);
}
