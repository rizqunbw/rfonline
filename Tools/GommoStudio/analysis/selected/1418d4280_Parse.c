/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/ifcfg.Parse
 * VA: 0x1418d4280
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_1400037e0: runtime.memequal
 * FUN_140009200: runtime.mapaccess2_faststr
 * FUN_1400094c0: runtime.mapassign_faststr
 * FUN_140016c60: runtime.newobject
 * FUN_140017560: runtime.wbMove
 * FUN_14005b8a0: runtime.slicebytetostring
 * FUN_140071a60: runtime.convT64
 * FUN_140071ae0: runtime.convTstring
 * FUN_140074a80: runtime.rand
 * FUN_1400762e0: runtime.makeslice
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c580: runtime.gcWriteBarrier1
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_1400e3100: strconv.Atoi
 * FUN_1400f0320: bytes.genSplit
 * FUN_1400f92a0: strings.ToUpper
 * FUN_140117060: fmt.Errorf
 * FUN_1418d4280: gommo/pkg/assets/ifcfg.Parse
 * FUN_1418d4ee0: gommo/pkg/assets/ifcfg.fields
 */
undefined1  [24] FUN_1418d4280(undefined8 param_1)

{
  undefined1 auVar1 [24];
  undefined1 auVar2 [24];
  undefined1 auVar3 [24];
  undefined1 auVar4 [24];
  undefined1 auVar5 [24];
  uint uVar6;
  uint uVar7;
  char cVar8;
  undefined8 extraout_RAX;
  undefined8 extraout_RAX_00;
  uint *puVar9;
  int *piVar10;
  int extraout_RAX_01;
  int extraout_RAX_02;
  int iVar11;
  undefined8 *puVar12;
  undefined8 uVar13;
  undefined8 extraout_RCX;
  undefined8 extraout_RCX_00;
  uint extraout_RCX_01;
  uint extraout_RCX_02;
  uint extraout_RCX_03;
  char extraout_BL;
  undefined8 extraout_RBX;
  uint uVar14;
  undefined8 extraout_RBX_00;
  int extraout_RBX_01;
  uint uVar15;
  uint extraout_RBX_02;
  uint extraout_RBX_03;
  uint extraout_RBX_04;
  undefined8 extraout_RSI;
  int iVar16;
  uint extraout_RSI_00;
  undefined8 *extraout_RDI;
  int extraout_R8;
  undefined8 extraout_R8_00;
  undefined8 *extraout_R11;
  undefined8 *extraout_R11_00;
  int *extraout_R11_01;
  undefined8 *extraout_R11_02;
  int unaff_R14;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar17 [16];
  undefined8 uStack0000000000000008;
  undefined8 auStack_308 [4];
  undefined8 uStack_2e8;
  uint uStack_2e0;
  int iStack_2d8;
  uint uStack_2d0;
  uint uStack_2c8;
  int iStack_2c0;
  int iStack_2b8;
  int iStack_2b0;
  int iStack_2a8;
  undefined8 uStack_2a0;
  undefined8 *puStack_298;
  uint *puStack_290;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  int iStack_1e0;
  int iStack_1d8;
  undefined8 *puStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 auStack_1a8 [25];
  undefined1 auStack_e0 [8];
  undefined8 uStack_d8;
  undefined8 *puStack_d0;
  internal_abi_Type *piStack_b0;
  undefined8 uStack_a8;
  internal_abi_Type *piStack_a0;
  undefined8 uStack_98;
  internal_abi_Type *piStack_90;
  undefined8 uStack_88;
  internal_abi_Type *piStack_80;
  undefined8 uStack_78;
  internal_abi_Type *piStack_70;
  undefined8 uStack_68;
  internal_abi_Type *piStack_60;
  undefined8 uStack_58;
  internal_abi_Type *piStack_50;
  undefined8 uStack_48;
  internal_abi_Type *piStack_40;
  undefined8 uStack_38;
  int iStack_30;
  undefined8 *puStack_28;
  int iStack_20;
  uint *puStack_18;
  int *piStack_10;

  uStack0000000000000008 = param_1;
  while (auStack_308 + 2 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  FUN_1400f0320();
  uStack_2a0 = extraout_RAX;
  puStack_1d0 = (undefined8 *)FUN_140016c60(&DAT_1426f5060);
  puStack_1d0[1] = extraout_RBX;
  puStack_1d0[2] = extraout_RCX;
  if (DAT_1444d6c60 != 0) {
    puStack_1d0 = (undefined8 *)FUN_14007c580();
    *extraout_R11 = uStack_2a0;
  }
  *puStack_1d0 = uStack_2a0;
  FUN_14007cc4b();
  auStack_1a8[0] = 0x8080808080808080;
  puStack_d0 = auStack_1a8;
  uStack_d8 = FUN_140074a80();
  piStack_10 = (int *)*puStack_1d0;
  iStack_2a8 = puStack_1d0[1];
  iStack_2c0 = 0;
  puVar12 = puStack_1d0;
  do {
    if (iStack_2a8 <= iStack_2c0) {
      return ZEXT824(puVar12);
    }
    uStack_2e0 = piStack_10[2];
    iStack_1d8 = *piStack_10;
    auVar17 = FUN_1418d4ee0(iStack_1d8,piStack_10[1],uStack_2e0);
    uVar14 = auVar17._8_8_;
    if (uVar14 == 0) {
      puVar12 = puStack_1d0;
    }
    else {
      if (uVar14 < 3) {
        uStack_1c8 = in_XMM15_Qa;
        uStack_1c0 = in_XMM15_Qb;
        uStack_1b8 = in_XMM15_Qa;
        uStack_1b0 = in_XMM15_Qb;
        puVar12 = &uStack_1c8;
        puVar9 = auVar17._0_8_;
      }
      else {
        puStack_290 = auVar17._0_8_;
        puVar12 = (undefined8 *)FUN_1400762e0(&string___String_type,uVar14,uVar14);
        puVar9 = puStack_290;
      }
      puStack_298 = puVar12;
      for (uVar15 = 0; (int)uVar15 < (int)uVar14; uVar15 = uVar15 + 1) {
        uVar7 = *puVar9;
        uVar6 = puVar9[1];
        if (uStack_2e0 < uVar6) {
                    /* WARNING: Subroutine does not return */
          FUN_14007c9c0(puVar9,uVar14,uVar6);
        }
        if (uVar6 < uVar7) {
                    /* WARNING: Subroutine does not return */
          FUN_14007ca00(uVar7,uVar14,uVar6);
        }
        uStack_2d0 = uVar15;
        puStack_18 = puVar9;
        auVar17 = FUN_14005b8a0(0,iStack_1d8 + (uVar7 & (int)(uVar7 - uStack_2e0) >> 0x3f),
                                uVar6 - uVar7);
        uVar6 = uStack_2d0;
        uVar13 = auVar17._0_8_;
        if (uVar14 <= uStack_2d0) {
                    /* WARNING: Subroutine does not return */
          FUN_14007c940(uStack_2d0);
        }
        puStack_298[uStack_2d0 * 2 + 1] = auVar17._8_8_;
        uVar15 = uStack_2d0;
        puVar12 = puStack_298;
        if (DAT_1444d6c60 != 0) {
          uVar13 = FUN_14007c5a0();
          *extraout_R11_02 = uVar13;
          extraout_R11_02[1] = extraout_R8_00;
          uVar15 = extraout_RSI_00;
          puVar12 = extraout_RDI;
        }
        puVar12[uVar6 * 2] = uVar13;
        puVar9 = puStack_18 + 2;
      }
      if (uVar14 == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940(0,0,0);
      }
      auVar17 = FUN_1400f92a0(*puVar12,puVar12[1]);
      iVar11 = auVar17._8_8_;
      piVar10 = auVar17._0_8_;
      if (iVar11 == 0xc) {
        if ((*piVar10 == 0x5f45525554584554) && ((sdword)piVar10[1] == 0x4f464e49)) {
          if (uVar14 != 6) {
            uStack_38 = FUN_140071a60(iStack_2c0 + 1);
            piStack_40 = &int___Int_type;
            auVar17 = FUN_140117060("ifcfg: line %d: TEXTURE_INFO takes index, group, file, width and height"
                                    ,0x47,&piStack_40,1,1);
            auVar1._16_8_ = 0;
            auVar1._0_16_ = auVar17;
            return auVar1 << 0x40;
          }
          uStack_280 = puStack_298[4];
          uStack_278 = puStack_298[5];
          uStack_270 = puStack_298[6];
          uStack_268 = puStack_298[7];
          uStack_250 = iStack_2c0;
          uStack_288 = FUN_1400e3100(puStack_298[2],puStack_298[3]);
          uStack_260 = FUN_1400e3100(puStack_298[8],puStack_298[9]);
          uStack_258 = FUN_1400e3100(puStack_298[10],puStack_298[0xb]);
          uVar14 = puStack_1d0[4] + 1;
          auVar17._8_8_ = uVar14;
          auVar17._0_8_ = puStack_1d0[3];
          if ((uint)puStack_1d0[5] < uVar14) {
            FUN_1400763c0(puStack_1d0[3],uVar14,puStack_1d0[5],1,
                          &gommo/pkg/assets/ifcfg::gommo_pkg_assets_ifcfg_Texture___Struct_type);
            puVar12 = puStack_1d0;
            auVar17._8_8_ = extraout_RBX_00;
            auVar17._0_8_ = extraout_RAX_00;
            puStack_1d0[5] = extraout_RCX_00;
            if (DAT_1444d6c60 != 0) {
              auVar17 = FUN_14007c5a0();
              *extraout_R11_00 = auVar17._0_8_;
              extraout_R11_00[1] = extraout_RSI;
            }
            puVar12[3] = auVar17._0_8_;
          }
          iVar11 = auVar17._0_8_;
          puStack_1d0[4] = auVar17._8_8_;
          iVar16 = (auVar17._8_8_ + -1) * 0x40;
          puVar12 = (undefined8 *)(iVar11 + iVar16);
          if (DAT_1444d6c60 != 0) {
            iStack_2b0 = iVar16;
            puStack_28 = puVar12;
            iStack_20 = iVar11;
            FUN_140017560(&gommo/pkg/assets/ifcfg::gommo_pkg_assets_ifcfg_Texture___Struct_type,
                          puVar12,&uStack_288);
            iVar11 = iStack_20;
            puVar12 = puStack_28;
            iVar16 = iStack_2b0;
          }
          iVar11 = iVar11 + iVar16;
          *puVar12 = uStack_288;
          puVar12[1] = uStack_280;
          puVar12[2] = uStack_278;
          puVar12[3] = uStack_270;
          *(undefined8 *)(iVar11 + 0x20) = uStack_268;
          *(undefined8 *)(iVar11 + 0x28) = uStack_260;
          *(undefined4 *)(iVar11 + 0x30) = (undefined4)uStack_258;
          *(undefined4 *)(iVar11 + 0x34) = uStack_258._4_4_;
          *(undefined4 *)(iVar11 + 0x38) = (undefined4)uStack_250;
          *(undefined4 *)(iVar11 + 0x3c) = uStack_250._4_4_;
          puVar12 = puStack_1d0;
        }
        else {
LAB_1418d471b:
          if (uVar14 != 9) {
            uStack_68 = FUN_140071a60(iStack_2c0 + 1,iVar11,0x5f45525554584554);
            piStack_70 = &int___Int_type;
            uStack_58 = FUN_140071ae0(*puStack_298,puStack_298[1]);
            piStack_60 = &string___String_type;
            uStack_48 = FUN_140071a60(uVar14 - 1);
            piStack_50 = &int___Int_type;
            auVar17 = FUN_140117060("ifcfg: line %d: %s has %d values, want 8 (tex, tex x, tex y, width, height, x, y, parent)"
                                    ,0x59,&piStack_70,3,3);
            auVar4._16_8_ = 0;
            auVar4._0_16_ = auVar17;
            return auVar4 << 0x40;
          }
          auVar17 = FUN_1400f92a0(*puStack_298,puStack_298[1]);
          puVar9 = (uint *)FUN_140009200(&map_string_int___Map_type,auStack_e0,auVar17._0_8_,
                                         auVar17._8_8_);
          if (extraout_BL != '\0') {
            uStack_2c8 = *puVar9;
            uStack_68 = FUN_140071a60(iStack_2c0 + 1);
            piStack_70 = &int___Int_type;
            auVar17 = FUN_140071ae0(*puStack_298,puStack_298[1]);
            uStack_58 = auVar17._0_8_;
            piStack_60 = &string___String_type;
            if ((uint)puStack_1d0[7] <= uStack_2c8) {
                    /* WARNING: Subroutine does not return */
              FUN_14007c940(uStack_2c8,auVar17._8_8_,puStack_1d0[7]);
            }
            uStack_48 = FUN_140071a60(*(int *)(puStack_1d0[6] + 0x68 + uStack_2c8 * 0x70) + 1);
            piStack_50 = &int___Int_type;
            auVar17 = FUN_140117060("ifcfg: line %d: %s is already on line %d",0x28,&piStack_70,3,3)
            ;
            auVar3._16_8_ = 0;
            auVar3._0_16_ = auVar17;
            return auVar3 << 0x40;
          }
          FUN_14007cc66();
          uStack_248 = *puStack_298;
          uStack_240 = puStack_298[1];
          uStack_210 = puStack_298[0xc];
          uStack_208 = puStack_298[0xd];
          uStack_200 = puStack_298[0xe];
          uStack_1f8 = puStack_298[0xf];
          uStack_1f0 = puStack_298[0x10];
          uStack_1e8 = puStack_298[0x11];
          iStack_1e0 = iStack_2c0;
          iVar11 = 0;
          auStack_308[0] = in_XMM15_Qa;
          auStack_308[1] = in_XMM15_Qa;
          auStack_308[2] = in_XMM15_Qb;
          auStack_308[3] = in_XMM15_Qa;
          uStack_2e8 = in_XMM15_Qb;
          while (iVar11 < 5) {
            iStack_2b0 = iVar11 + 1;
            iStack_2b8 = iStack_2b0 * 0x10;
            iStack_2d8 = iVar11;
            auVar17 = FUN_1400e3100(puStack_298[iStack_2b0 * 2],puStack_298[iStack_2b0 * 2 + 1]);
            auStack_308[iStack_2d8] = auVar17._0_8_;
            if (auVar17._8_8_ != 0) {
              uStack_a8 = FUN_140071a60(iStack_2c0 + 1);
              piStack_b0 = &int___Int_type;
              uStack_98 = FUN_140071ae0(*puStack_298,puStack_298[1]);
              piStack_a0 = &string___String_type;
              uStack_88 = FUN_140071a60(iStack_2b0);
              piStack_90 = &int___Int_type;
              uStack_78 = FUN_140071ae0(*(undefined8 *)((int)puStack_298 + iStack_2b8),
                                        *(undefined8 *)((int)puStack_298 + iStack_2b8 + 8));
              piStack_80 = &string___String_type;
              auVar17 = FUN_140117060("ifcfg: line %d: %s value %d is %q, not a number",0x2f,
                                      &piStack_b0,4,4);
              auVar5._16_8_ = 0;
              auVar5._0_16_ = auVar17;
              return auVar5 << 0x40;
            }
            iVar11 = iStack_2b0;
          }
          uStack_238 = auStack_308[0];
          uStack_230 = auStack_308[1];
          uStack_228 = auStack_308[2];
          uStack_220 = auStack_308[3];
          uStack_218 = uStack_2e8;
          auVar17 = FUN_1400f92a0(*puStack_298,puStack_298[1]);
          iStack_2b0 = puStack_1d0[7];
          piVar10 = (int *)FUN_1400094c0(&map_string_int___Map_type,auStack_e0,auVar17._0_8_,
                                         auVar17._8_8_);
          *piVar10 = iStack_2b0;
          uVar14 = puStack_1d0[8];
          uVar15 = puStack_1d0[7] + 1;
          iVar11 = puStack_1d0[6];
          if (uVar14 < uVar15) {
            FUN_1400763c0(iVar11,uVar15,uVar14,1,
                          &gommo/pkg/assets/ifcfg::gommo_pkg_assets_ifcfg_Row___Struct_type);
            puVar12 = puStack_1d0;
            puStack_1d0[8] = extraout_RCX_01;
            iVar11 = extraout_RAX_01;
            uVar14 = extraout_RCX_01;
            uVar15 = extraout_RBX_02;
            if (DAT_1444d6c60 != 0) {
              FUN_14007c5a0();
              *extraout_R11_01 = extraout_RAX_02;
              extraout_R11_01[1] = extraout_R8;
              iVar11 = extraout_RAX_02;
              uVar14 = extraout_RCX_02;
              uVar15 = extraout_RBX_03;
            }
            puVar12[6] = iVar11;
          }
          puStack_1d0[7] = uVar15;
          iVar11 = uVar15 * 0x70 + iVar11 + -0x70;
          if (DAT_1444d6c60 != 0) {
            iStack_30 = iVar11;
            FUN_140017560(&gommo/pkg/assets/ifcfg::gommo_pkg_assets_ifcfg_Row___Struct_type,iVar11,
                          &uStack_248);
            uVar14 = extraout_RCX_03;
            uVar15 = extraout_RBX_04;
            iVar11 = iStack_30;
          }
          puVar12 = (undefined8 *)FUN_14007cfbe(puStack_1d0,uVar15,uVar14,iVar11,&uStack_248);
        }
      }
      else {
        if ((iVar11 != 0x16) ||
           (cVar8 = FUN_1400037e0(piVar10,"NUMBER_OF_TEXTURE_INFO",0x16), iVar11 = extraout_RBX_01,
           cVar8 == '\0')) goto LAB_1418d471b;
        if (uVar14 != 2) {
          uStack_38 = FUN_140071a60(iStack_2c0 + 1);
          piStack_40 = &int___Int_type;
          auVar17 = FUN_140117060("ifcfg: line %d: NUMBER_OF_TEXTURE_INFO takes one value",0x36,
                                  &piStack_40,1,1);
          auVar2._16_8_ = 0;
          auVar2._0_16_ = auVar17;
          return auVar2 << 0x40;
        }
        uVar13 = FUN_1400e3100(puStack_298[2],puStack_298[3]);
        puStack_1d0[9] = uVar13;
        puVar12 = puStack_1d0;
      }
    }
    piStack_10 = piStack_10 + 3;
    iStack_2c0 = iStack_2c0 + 1;
  } while( true );
}
