/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/r3char.LoadSkeleton
 * VA: 0x1406707c0
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140009200: runtime.mapaccess2_faststr
 * FUN_1400094c0: runtime.mapassign_faststr
 * FUN_140016c60: runtime.newobject
 * FUN_140017560: runtime.wbMove
 * FUN_140072200: runtime.makemap
 * FUN_1400762e0: runtime.makeslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_1400f92a0: strings.ToUpper
 * FUN_1400fae40: strings.EqualFold
 * FUN_1405afae0: gommo/pkg/assets/fixstr.CString
 * FUN_14066ce80: gommo/pkg/assets/r3char.LoadModel
 * FUN_1406707c0: gommo/pkg/assets/r3char.LoadSkeleton
 * FUN_140670d00: gommo/pkg/assets/r3char.(*Skeleton).repairLocals
 */
undefined1  [24] FUN_1406707c0(undefined8 param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 auVar3 [24];
  char cVar4;
  undefined8 *extraout_RAX;
  int *piVar5;
  undefined8 extraout_RAX_00;
  undefined8 extraout_RCX;
  int iVar6;
  uint extraout_RCX_00;
  uint uVar7;
  int extraout_RBX;
  undefined8 extraout_RBX_00;
  undefined8 extraout_RBX_01;
  undefined8 uVar8;
  undefined8 extraout_RBX_02;
  int iVar9;
  undefined8 *puVar10;
  int extraout_R9;
  int *extraout_R11;
  int unaff_R14;
  undefined1 auVar11 [16];
  undefined8 uStack0000000000000008;
  undefined8 uStack_348;
  undefined1 auStack_330 [80];
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 uStack_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
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
  undefined4 uStack_230;
  undefined4 uStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined8 uStack_148;
  uint uStack_138;
  undefined8 *puStack_128;
  undefined8 uStack_120;
  int iStack_118;
  int iStack_110;
  int iStack_108;
  undefined8 auStack_100 [4];
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_18 [16];

  uStack0000000000000008 = param_1;
  while (auStack_330 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  FUN_14066ce80();
  if (extraout_RBX != 0) {
    auVar3._8_8_ = extraout_RCX;
    auVar3._0_8_ = extraout_RBX;
    auVar3._16_8_ = 0;
    return auVar3 << 0x40;
  }
  uVar8 = extraout_RAX[1];
  puStack_128 = extraout_RAX;
  iStack_108 = FUN_1400762e0(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Bone___Struct_type,
                             uVar8);
  iStack_110 = FUN_140072200(&map_string_int___Map_type,puStack_128[1],0);
  auVar11 = FUN_140016c60(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Skeleton___Struct_type);
  *(undefined8 *)(auVar11._0_8_ + 8) = uVar8;
  *(undefined8 *)(auVar11._0_8_ + 0x10) = uVar8;
  if (DAT_1444d6c60 != 0) {
    auVar11 = FUN_14007c5a0();
    *extraout_R11 = iStack_108;
    extraout_R11[1] = iStack_110;
  }
  uVar8 = auVar11._8_8_;
  piVar5 = auVar11._0_8_;
  *piVar5 = iStack_108;
  piVar5[3] = iStack_110;
  puVar10 = (undefined8 *)*puStack_128;
  iVar1 = puStack_128[1];
  iVar6 = 0;
  while( true ) {
    if (iVar1 <= iVar6) {
      iVar6 = piVar5[1];
      uVar7 = 0;
      while( true ) {
        if (iVar6 <= (int)uVar7) {
          FUN_140670d00();
          return ZEXT824(piVar5);
        }
        if ((uint)piVar5[1] <= uVar7) break;
        iVar9 = uVar7 * 0xf8;
        iVar1 = *(int *)(*piVar5 + 0x18 + iVar9);
        uVar2 = *(undefined8 *)(*piVar5 + 0x10 + iVar9);
        uVar8 = 0;
        if (iVar1 != 0) {
          cVar4 = FUN_1400fae40(uVar2,iVar1,"NULL",4);
          if (cVar4 == '\0') {
            auVar11 = FUN_1400f92a0(uVar2,iVar1);
            auVar11 = FUN_140009200(&map_string_int___Map_type,piVar5[3],auVar11._0_8_,auVar11._8_8_
                                   );
            uVar8 = auVar11._8_8_;
            if ((auVar11[8] != '\0') && (uVar7 != *auVar11._0_8_)) {
              if ((uint)piVar5[1] <= uVar7) {
                    /* WARNING: Subroutine does not return */
                FUN_14007c940();
              }
              *(uint *)(*piVar5 + 0xe0 + iVar9) = *auVar11._0_8_;
            }
          }
          else {
            uVar8 = extraout_RBX_02;
          }
        }
        uVar7 = uVar7 + 1;
      }
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(uVar7,uVar8,piVar5[1]);
    }
    uVar8 = *puVar10;
    FUN_14007ce44();
    if (uStack_138 < 100) break;
    iStack_108 = extraout_R9;
    FUN_1405afae0(uStack_148,100,uStack_138);
    auStack_100[0] = 0;
    auVar11 = FUN_14007cf4e();
    uStack_e0 = uStack_2e0;
    uStack_d8 = uStack_2d8;
    uStack_d0 = uStack_2d0;
    uStack_c8 = uStack_2c8;
    uStack_c0 = uStack_2c0;
    uStack_b8 = uStack_2b8;
    uStack_b0 = uStack_2b0;
    uStack_a8 = uStack_2a8;
    uStack_a0 = uStack_2a0;
    uStack_98 = uStack_298;
    uStack_90 = uStack_290;
    uStack_88 = uStack_288;
    uStack_80 = uStack_280;
    uStack_78 = uStack_278;
    uStack_70 = uStack_270;
    uStack_68 = uStack_268;
    uStack_60 = uStack_260;
    uStack_58 = uStack_258;
    uStack_50 = uStack_250;
    uStack_48 = uStack_248;
    uStack_40 = uStack_240;
    uStack_38 = uStack_238;
    uStack_30 = uStack_230;
    uStack_2c = uStack_22c;
    uStack_28 = uStack_228;
    uStack_24 = uStack_224;
    auStack_100[0] = uVar8;
    auStack_18 = auVar11;
    if ((uint)piVar5[1] <= extraout_RCX_00) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940();
    }
    iVar6 = *piVar5;
    if (DAT_1444d6c60 != 0) {
      iStack_118 = iVar6;
      FUN_140017560(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Bone___Struct_type,
                    iVar6 + extraout_RCX_00 * 0xf8,auStack_100);
      iVar6 = iStack_118;
    }
    *(undefined8 *)(iVar6 + extraout_RCX_00 * 0xf8) = auStack_100[0];
    FUN_14007cf4e();
    auVar11 = FUN_1400f92a0(uVar8,uStack_348);
    uStack_120 = auVar11._0_8_;
    FUN_140009200(&map_string_int___Map_type,piVar5[3],uStack_120,auVar11._8_8_);
    uVar8 = extraout_RBX_01;
    if ((char)extraout_RBX_01 == '\0') {
      auVar11 = FUN_1400094c0(&map_string_int___Map_type,piVar5[3],uStack_120,auVar11._8_8_);
      uVar8 = auVar11._8_8_;
      *auVar11._0_8_ = extraout_RCX_00;
    }
    puVar10 = (undefined8 *)(iStack_108 + 0x228);
    iVar6 = extraout_RCX_00 + 1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_14007c9c0(extraout_RAX_00,extraout_RBX_00,100);
}
