/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/r3.LoadBSP
 * VA: 0x140694de0
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_1400087a0: runtime.mapassign_fast64
 * FUN_1400094c0: runtime.mapassign_faststr
 * FUN_140013220: runtime.convT32
 * FUN_140016c60: runtime.newobject
 * FUN_140017560: runtime.wbMove
 * FUN_140071a60: runtime.convT64
 * FUN_1400721c0: runtime.makemap_small
 * FUN_140072200: runtime.makemap
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c580: runtime.gcWriteBarrier1
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_14007d340: runtime.memmove
 * FUN_140117060: fmt.Errorf
 * FUN_140694de0: gommo/pkg/assets/r3.LoadBSP
 * FUN_140695d00: gommo/pkg/assets/r3.(*BSP).parseLumps
 */
undefined1  [24] FUN_140694de0(sdword *param_1,int param_2)

{
  dword dVar1;
  undefined1 auVar2 [24];
  undefined1 auVar3 [24];
  undefined1 auVar4 [24];
  undefined1 auVar5 [24];
  int extraout_RAX;
  undefined8 *puVar6;
  undefined8 *extraout_RAX_00;
  undefined8 *extraout_RAX_01;
  undefined8 *extraout_RAX_02;
  undefined8 *extraout_RAX_03;
  undefined8 uVar7;
  int *piVar8;
  uint extraout_RCX;
  uint extraout_RCX_00;
  uint extraout_RCX_01;
  uint extraout_RCX_02;
  uint extraout_RCX_03;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int extraout_RBX;
  uint extraout_RBX_00;
  uint extraout_RBX_01;
  uint extraout_RBX_02;
  uint extraout_RBX_03;
  uint extraout_RBX_04;
  uint uVar12;
  int iVar13;
  undefined4 *extraout_RSI;
  undefined4 *puVar14;
  int extraout_RSI_00;
  int extraout_RSI_01;
  int iVar15;
  undefined8 extraout_RDI;
  int extraout_R8;
  int extraout_R9;
  uint uVar16;
  undefined8 *extraout_R11;
  undefined8 *extraout_R11_00;
  int *extraout_R11_01;
  int *extraout_R11_02;
  uint uVar17;
  int unaff_R14;
  bool bVar18;
  undefined8 *in_XMM15_Qa;
  undefined1 auVar19 [16];
  sdword *psStack0000000000000008;
  dword adStack_640 [16];
  undefined1 auStack_600 [4];
  dword adStack_5fc [16];
  sdword sStack_5bc;
  dword adStack_4e4 [20];
  dword adStack_494 [63];
  int iStack_398;
  uint uStack_390;
  uint uStack_388;
  int iStack_380;
  uint uStack_378;
  int iStack_370;
  uint uStack_368;
  int iStack_360;
  int iStack_358;
  uint uStack_350;
  uint uStack_348;
  int iStack_340;
  uint uStack_338;
  uint uStack_330;
  int iStack_328;
  int iStack_320;
  uint uStack_318;
  uint uStack_310;
  int iStack_308;
  int iStack_300;
  uint uStack_2f8;
  uint uStack_2f0;
  sdword *psStack_2e8;
  int iStack_2e0;
  undefined8 uStack_2d8;
  uint uStack_2d0;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined4 uStack_2c0;
  undefined4 uStack_2bc;
  undefined4 *puStack_2b8;
  undefined8 uStack_2b0;
  undefined8 *puStack_2a8;
  undefined8 auStack_2a0 [41];
  undefined1 auStack_158 [16];
  undefined8 *puStack_148;
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  int iStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  int iStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  char *pcStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  int iStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  int iStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  internal_abi_Type *piStack_68;
  undefined8 uStack_60;
  internal_abi_Type *piStack_58;
  char *pcStack_50;
  dword *pdStack_48;
  undefined8 *puStack_40;
  undefined8 *puStack_38;
  undefined8 *puStack_30;
  undefined8 *puStack_28;
  undefined8 *puStack_20;
  undefined8 *puStack_18;
  undefined8 *puStack_10;

  psStack0000000000000008 = param_1;
  while (auStack_600 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  if (param_2 < 0x2ac) {
    uStack_60 = FUN_140071a60(param_2);
    piStack_68 = &int___Int_type;
    piStack_58 = &int___Int_type;
    pcStack_50 = &DAT_142f3bcb8;
    auVar19 = FUN_140117060("r3: bsp is %d bytes, shorter than its %d-byte header",0x34,&piStack_68,
                            2,2);
    auVar3._16_8_ = 0;
    auVar3._0_16_ = auVar19;
    return auVar3 << 0x40;
  }
  if (*psStack0000000000000008 != 0x27) {
    uStack_60 = FUN_140013220(*psStack0000000000000008);
    piStack_68 = &uint32___Uint32_type;
    piStack_58 = &int___Int_type;
    pcStack_50 = "\'";
    auVar19 = FUN_140117060("r3: bsp version %d, want %d",0x1b,&piStack_68,2,2);
    auVar2._16_8_ = 0;
    auVar2._0_16_ = auVar19;
    return auVar2 << 0x40;
  }
  FUN_14007cb9c();
  for (iVar10 = 0; iVar10 < 0x55; iVar10 = iVar10 + 1) {
    dVar1 = *(dword *)(extraout_RAX + 8 + iVar10 * 8);
    adStack_640[iVar10 * 2] = *(dword *)(extraout_RAX + 4 + iVar10 * 8);
    adStack_640[iVar10 * 2 + 1] = dVar1;
  }
  if ((adStack_640[0xf] == 0) && (adStack_640[0xb] / 0x58 != 0)) {
    iVar10 = -1;
    if (sStack_5bc == (sdword)((sdword)(adStack_640[0xb] / 0x58) * 2)) {
      iVar10 = 8;
    }
  }
  else {
    iVar10 = -1;
  }
  iStack_360 = iVar10;
  uStack_2f0 = slice_8__14416f8d0.len;
  iVar15 = 0x2ac;
  uVar16 = 0;
  puStack_40 = (undefined8 *)0x0;
  uVar17 = 0;
  uVar12 = 0;
  puVar6 = slice_8__14416f8d0.array;
  uVar9 = slice_8__14416f8d0.len;
  psStack0000000000000008 = (sdword *)extraout_RAX;
  while ((int)uVar12 < (int)uVar9) {
    if (7 < uVar12) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(uVar12,extraout_RBX,8);
    }
    uStack_368 = uVar12;
    puStack_10 = puVar6;
    uStack_78 = (uint)adStack_640[uVar12 * 2 + 1];
    uVar17 = uVar17 + 1;
    uStack_98 = *puVar6;
    uStack_90 = puVar6[1];
    uStack_88 = puVar6[2];
    iStack_80 = iVar15;
    uStack_70 = uVar12;
    uVar12 = uStack_78;
    iVar13 = iVar15;
    if (uVar16 < uVar17) {
      iStack_398 = iVar15;
      uStack_2f8 = uStack_78;
      FUN_1400763c0(puStack_40,uVar17,uVar16,1,
                    &gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type);
      iVar10 = iStack_360;
      uVar12 = uStack_2f8;
      iVar13 = iStack_398;
      uVar9 = uStack_2f0;
      uVar16 = extraout_RCX_00;
      puStack_40 = extraout_RAX_00;
      uVar17 = extraout_RBX_00;
    }
    puVar6 = puStack_40 + uVar17 * 6 + -6;
    iVar15 = uVar12 + iVar13;
    uVar11 = uVar17 * 0x30;
    if (DAT_1444d6c60 != 0) {
      uStack_390 = uVar17;
      uStack_388 = uVar16;
      iStack_300 = uVar12 + iVar13;
      uStack_2f8 = uVar17 * 0x30;
      puStack_2a8 = puStack_40;
      puStack_18 = puVar6;
      FUN_140017560(&gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type,puVar6,&uStack_98
                   );
      puVar6 = puStack_18;
      iVar15 = iStack_300;
      iVar10 = iStack_360;
      uVar9 = uStack_2f0;
      uVar16 = uStack_388;
      puStack_40 = puStack_2a8;
      uVar17 = uStack_390;
      uVar11 = uStack_2f8;
    }
    *puVar6 = uStack_98;
    puVar6[1] = uStack_90;
    *(undefined8 *)((int)puStack_40 + (uVar11 - 0x20)) = uStack_88;
    *(int *)((int)puStack_40 + (uVar11 - 0x18)) = iStack_80;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 0x10)) = (undefined4)uStack_78;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 0xc)) = uStack_78._4_4_;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 8)) = (undefined4)uStack_70;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 4)) = uStack_70._4_4_;
    puVar6 = puStack_10 + 3;
    uVar12 = uStack_368 + 1;
  }
  iVar13 = 0;
  while (iVar13 < 0x23) {
    iStack_370 = iVar13;
    puStack_20 = puStack_40;
    uStack_2f0 = (uint)adStack_5fc[iVar13 * 2];
    uVar17 = uVar17 + 1;
    bVar18 = iVar10 == iVar13;
    uStack_c0 = 5;
    if (bVar18) {
      uStack_c0 = 0xd;
    }
    uStack_b8 = 1;
    if (bVar18) {
      uStack_b8 = 2;
    }
    pcStack_c8 = &DAT_14291b6f9;
    if (bVar18) {
      pcStack_c8 = "EventObjectID";
    }
    iStack_b0 = iVar15;
    uStack_a8 = uStack_2f0;
    uStack_a0 = iVar13 + 8;
    if (uVar16 < uVar17) {
      iStack_308 = iVar15;
      FUN_1400763c0(puStack_40,uVar17,uVar16,1,
                    &gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type);
      puStack_40 = extraout_RAX_01;
      iVar15 = iStack_308;
      uVar17 = extraout_RBX_01;
      uVar16 = extraout_RCX_01;
    }
    else {
    }
    puVar6 = puStack_40 + uVar17 * 6 + -6;
    iVar15 = uStack_2f0 + iVar15;
    uStack_2f0 = uVar17 * 0x30;
    if (DAT_1444d6c60 != 0) {
      iStack_320 = iVar15;
      uStack_318 = uVar16;
      uStack_310 = uVar17;
      puStack_28 = puStack_40;
      puStack_18 = puVar6;
      FUN_140017560(&gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type,puVar6,
                    &pcStack_c8);
      puStack_40 = puStack_28;
      iVar15 = iStack_320;
      uVar17 = uStack_310;
      uVar16 = uStack_318;
      puVar6 = puStack_18;
    }
    *puVar6 = pcStack_c8;
    puVar6[1] = uStack_c0;
    *(undefined8 *)((int)puStack_40 + uStack_2f0 + -0x20) = uStack_b8;
    *(int *)((int)puStack_40 + uStack_2f0 + -0x18) = iStack_b0;
    *(undefined4 *)((int)puStack_40 + uStack_2f0 + -0x10) = (undefined4)uStack_a8;
    *(undefined4 *)((int)puStack_40 + uStack_2f0 + -0xc) = uStack_a8._4_4_;
    *(undefined4 *)((int)puStack_40 + uStack_2f0 + -8) = (undefined4)uStack_a0;
    *(undefined4 *)((int)puStack_40 + uStack_2f0 + -4) = uStack_a0._4_4_;
    iVar10 = iStack_360;
    iVar13 = iStack_370 + 1;
  }
  uStack_2f0 = slice_10__14416f8f0.len;
  uVar12 = 0;
  puVar6 = slice_10__14416f8f0.array;
  uVar9 = slice_10__14416f8f0.len;
  while ((int)uVar12 < (int)uVar9) {
    if (9 < uVar12) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(uVar12,extraout_RBX,10);
    }
    uStack_378 = uVar12;
    puStack_10 = puVar6;
    uStack_d8 = (uint)adStack_4e4[uVar12 * 2];
    uVar17 = uVar17 + 1;
    uStack_f8 = *puVar6;
    uStack_f0 = puVar6[1];
    uStack_e8 = puVar6[2];
    iStack_e0 = iVar15;
    uStack_d0 = uVar12 + 0x2b;
    uVar12 = uStack_d8;
    iVar10 = iVar15;
    if (uVar16 < uVar17) {
      iStack_328 = iVar15;
      uStack_2f8 = uStack_d8;
      FUN_1400763c0(puStack_40,uVar17,uVar16,1,
                    &gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type);
      uVar12 = uStack_2f8;
      iVar10 = iStack_328;
      uVar9 = uStack_2f0;
      uVar16 = extraout_RCX_02;
      puStack_40 = extraout_RAX_02;
      uVar17 = extraout_RBX_02;
    }
    puVar6 = puStack_40 + uVar17 * 6 + -6;
    uVar11 = uVar17 * 0x30;
    iVar15 = uVar12 + iVar10;
    if (DAT_1444d6c60 != 0) {
      iStack_340 = uVar12 + iVar10;
      uStack_338 = uVar16;
      uStack_330 = uVar17;
      uStack_2f8 = uVar17 * 0x30;
      puStack_30 = puStack_40;
      puStack_18 = puVar6;
      FUN_140017560(&gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type,puVar6,&uStack_f8
                   );
      uVar11 = uStack_2f8;
      uVar9 = uStack_2f0;
      puVar6 = puStack_18;
      uVar16 = uStack_338;
      puStack_40 = puStack_30;
      uVar17 = uStack_330;
      iVar15 = iStack_340;
    }
    *puVar6 = uStack_f8;
    puVar6[1] = uStack_f0;
    *(undefined8 *)((int)puStack_40 + (uVar11 - 0x20)) = uStack_e8;
    *(int *)((int)puStack_40 + (uVar11 - 0x18)) = iStack_e0;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 0x10)) = (undefined4)uStack_d8;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 0xc)) = uStack_d8._4_4_;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 8)) = (undefined4)uStack_d0;
    *(undefined4 *)((int)puStack_40 + (uVar11 - 4)) = uStack_d0._4_4_;
    puVar6 = puStack_10 + 3;
    uVar12 = uStack_378 + 1;
  }
  iVar10 = 0;
  while (iVar10 < 0x20) {
    iStack_380 = iVar10;
    uStack_108 = (uint)adStack_494[iVar10 * 2];
    uVar17 = uVar17 + 1;
    puStack_128 = &DAT_14291b6f9;
    uStack_120 = 5;
    uStack_118 = 1;
    iStack_110 = iVar15;
    uStack_100 = iVar10 + 0x35;
    iVar10 = iVar15;
    uVar9 = uStack_108;
    if (uVar16 < uVar17) {
      iStack_398 = iVar15;
      uStack_2f0 = uStack_108;
      FUN_1400763c0(puStack_40,uVar17,uVar16,1,
                    &gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type);
      iVar10 = iStack_398;
      uVar9 = uStack_2f0;
      uVar17 = extraout_RBX_03;
      uVar16 = extraout_RCX_03;
      puStack_40 = extraout_RAX_03;
    }
    puVar6 = puStack_40 + uVar17 * 6 + -6;
    iVar15 = uVar9 + iVar10;
    uVar12 = uVar17 * 0x30;
    if (DAT_1444d6c60 != 0) {
      iStack_358 = uVar9 + iVar10;
      uStack_350 = uVar16;
      uStack_348 = uVar17;
      uStack_2f0 = uVar17 * 0x30;
      puStack_38 = puStack_40;
      puStack_18 = puVar6;
      FUN_140017560(&gommo/pkg/assets/r3::gommo_pkg_assets_r3_placed___Struct_type,puVar6,
                    &puStack_128);
      iVar15 = iStack_358;
      uVar12 = uStack_2f0;
      uVar17 = uStack_348;
      uVar16 = uStack_350;
      puStack_40 = puStack_38;
      puVar6 = puStack_18;
    }
    *puVar6 = puStack_128;
    puVar6[1] = uStack_120;
    *(undefined8 *)((int)puStack_40 + (uVar12 - 0x20)) = uStack_118;
    *(int *)((int)puStack_40 + (uVar12 - 0x18)) = iStack_110;
    *(undefined4 *)((int)puStack_40 + (uVar12 - 0x10)) = (undefined4)uStack_108;
    *(undefined4 *)((int)puStack_40 + (uVar12 - 0xc)) = uStack_108._4_4_;
    *(undefined4 *)((int)puStack_40 + (uVar12 - 8)) = (undefined4)uStack_100;
    *(undefined4 *)((int)puStack_40 + (uVar12 - 4)) = uStack_100._4_4_;
    iVar10 = iStack_380 + 1;
  }
  if (extraout_RBX != iVar15) {
    uStack_60 = FUN_140071a60(iVar15,extraout_RBX,extraout_RCX);
    piStack_68 = &int___Int_type;
    pcStack_50 = (char *)FUN_140071a60(extraout_RBX);
    piStack_58 = &int___Int_type;
    auVar19 = FUN_140117060("r3: bsp lump sizes sum to %d but the file is %d bytes",0x35,&piStack_68
                            ,2,2);
    auVar4._16_8_ = 0;
    auVar4._0_16_ = auVar19;
    return auVar4 << 0x40;
  }
  uStack_390 = uVar17;
  pdStack_48 = (dword *)FUN_140016c60(&gommo/pkg/assets/r3::
                                       _85_gommo_pkg_assets_r3_entry___Array_type);
  puStack_2b8 = (undefined4 *)
                FUN_140016c60(&gommo/pkg/assets/r3::gommo_pkg_assets_r3_BSP___Struct_type);
  *puStack_2b8 = 0x27;
  if (DAT_1444d6c60 != 0) {
    puStack_2b8 = (undefined4 *)FUN_14007c580();
    *extraout_R11 = pdStack_48;
  }
  *(dword **)(puStack_2b8 + 0x6e) = pdStack_48;
  *(undefined8 *)(puStack_2b8 + 0x78) = 7;
  if (pdStack_48 != adStack_640) {
    FUN_14007d340(pdStack_48,adStack_640,0x2a8);
  }
  if (-1 < iStack_360) {
    *(int *)(puStack_2b8 + 0x78) = iStack_360 + 8;
  }
  uVar17 = uStack_390;
  puStack_148 = in_XMM15_Qa;
  if ((int)uStack_390 < 9) {
    FUN_14007cc1d();
    auStack_2a0[0] = 0x8080808080808080;
    puStack_148 = auStack_2a0;
    uVar17 = extraout_RBX_04;
  }
  uVar7 = FUN_140072200(&map_string___uint8___Map_type,uVar17,auStack_158);
  uVar9 = 0;
  puVar6 = puStack_40;
  uVar17 = uStack_390;
  uStack_2b0 = uVar7;
  do {
    if ((int)uVar17 <= (int)uVar9) {
      auVar19 = FUN_140695d00(puStack_2b8,uVar7);
      if (auVar19._0_8_ == 0) {
        return ZEXT824(puStack_2b8);
      }
      auVar5._16_8_ = 0;
      auVar5._0_16_ = auVar19;
      return auVar5 << 0x40;
    }
    psStack_2e8 = (sdword *)*puVar6;
    iStack_2e0 = puVar6[1];
    uStack_2d8 = puVar6[2];
    uStack_2d0 = puVar6[3];
    piVar8 = puVar6 + 4;
    uStack_2c8 = (undefined4)*piVar8;
    uStack_2c4 = *(undefined4 *)((int)puVar6 + 0x24);
    uStack_2c0 = *(undefined4 *)(puVar6 + 5);
    uStack_2bc = *(undefined4 *)((int)puVar6 + 0x2c);
    uStack_2f0 = uVar9;
    puStack_10 = puVar6;
    if (((iStack_2e0 == 5) && (*psStack_2e8 == 0x72617073)) && ((char)psStack_2e8[1] == 'e')) {
      if (0 < *piVar8) {
        puVar14 = puStack_2b8;
        if (*(int *)(puStack_2b8 + 0x70) == 0) {
          uVar7 = FUN_1400721c0();
          if (DAT_1444d6c60 == 0) {
            puVar14 = puStack_2b8;
          }
          else {
            uVar7 = FUN_14007c5a0();
            *extraout_R11_00 = uVar7;
            extraout_R11_00[1] = extraout_RDI;
            puVar14 = extraout_RSI;
          }
          *(undefined8 *)(puVar14 + 0x70) = uVar7;
          uVar7 = uStack_2b0;
          uVar17 = uStack_390;
        }
        uVar9 = CONCAT44(uStack_2c4,uStack_2c8) + uStack_2d0;
        if (extraout_RCX < uVar9) {
                    /* WARNING: Subroutine does not return */
          FUN_14007c9c0(uVar7,uVar17,uVar9);
        }
        if (uVar9 < uStack_2d0) {
                    /* WARNING: Subroutine does not return */
          FUN_14007ca00(uStack_2d0,uVar17,uVar9);
        }
        uStack_2f8 = uStack_2d0;
        iStack_300 = CONCAT44(uStack_2c4,uStack_2c8);
        piVar8 = (int *)FUN_1400087a0(&map_int___uint8___Map_type,*(undefined8 *)(puVar14 + 0x70),
                                      CONCAT44(uStack_2bc,uStack_2c0));
        piVar8[1] = iStack_300;
        piVar8[2] = extraout_RCX - uStack_2f8;
        iVar10 = (uStack_2f8 & (int)-(extraout_RCX - uStack_2f8) >> 0x3f) +
                 (int)psStack0000000000000008;
        if (DAT_1444d6c60 != 0) {
          piVar8 = (int *)FUN_14007c5a0();
          *extraout_R11_01 = extraout_RSI_00;
          extraout_R11_01[1] = extraout_R8;
          iVar10 = extraout_RSI_00;
        }
        *piVar8 = iVar10;
        uVar7 = uStack_2b0;
        uVar17 = uStack_390;
      }
    }
    else {
      uVar9 = *piVar8 + uStack_2d0;
      if (extraout_RCX < uVar9) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c9c0(uVar7,uVar17,uVar9);
      }
      if (uVar9 < uStack_2d0) {
                    /* WARNING: Subroutine does not return */
        FUN_14007ca00(uStack_2d0,uVar17,uVar9);
      }
      iStack_300 = *piVar8;
      uStack_2f8 = uStack_2d0;
      piVar8 = (int *)FUN_1400094c0(&map_string___uint8___Map_type,uVar7,psStack_2e8);
      piVar8[1] = iStack_300;
      piVar8[2] = extraout_RCX - uStack_2f8;
      iVar10 = (uStack_2f8 & (int)-(extraout_RCX - uStack_2f8) >> 0x3f) +
               (int)psStack0000000000000008;
      if (DAT_1444d6c60 != 0) {
        piVar8 = (int *)FUN_14007c5a0();
        *extraout_R11_02 = extraout_RSI_01;
        extraout_R11_02[1] = extraout_R9;
        iVar10 = extraout_RSI_01;
      }
      *piVar8 = iVar10;
      uVar7 = uStack_2b0;
      uVar17 = uStack_390;
    }
    puVar6 = puStack_10 + 6;
    uVar9 = uStack_2f0 + 1;
  } while( true );
}
