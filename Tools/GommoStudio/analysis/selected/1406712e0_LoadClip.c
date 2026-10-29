/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/r3char.LoadClip
 * VA: 0x1406712e0
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140016c60: runtime.newobject
 * FUN_140017560: runtime.wbMove
 * FUN_140071a60: runtime.convT64
 * FUN_1400762e0: runtime.makeslice
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c580: runtime.gcWriteBarrier1
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c940: runtime.panicIndex
 * FUN_140117060: fmt.Errorf
 * FUN_14066cac0: gommo/pkg/assets/r3char.(*reader).need
 * FUN_14066cbe0: gommo/pkg/assets/r3char.(*reader).u16
 * FUN_14066cc80: gommo/pkg/assets/r3char.(*reader).u32
 * FUN_14066cd20: gommo/pkg/assets/r3char.(*reader).vec3
 * FUN_14066cda0: gommo/pkg/assets/r3char.(*reader).str
 * FUN_1406712e0: gommo/pkg/assets/r3char.LoadClip
 */
undefined1  [24] FUN_1406712e0(undefined8 param_1,int param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [24];
  undefined1 auVar4 [24];
  undefined1 auVar5 [24];
  undefined1 auVar6 [24];
  undefined1 auVar7 [24];
  undefined1 auVar8 [24];
  undefined1 auVar9 [24];
  undefined1 auVar10 [24];
  char cVar11;
  ushort uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  int *piVar17;
  int extraout_RAX;
  int extraout_RAX_00;
  uint uVar18;
  int iVar19;
  uint extraout_RCX;
  uint extraout_RCX_00;
  uint extraout_RCX_01;
  undefined4 *puVar20;
  int iVar21;
  uint uVar22;
  uint extraout_RBX;
  uint extraout_RBX_00;
  int extraout_RBX_01;
  int extraout_R8;
  int iVar23;
  int *extraout_R11;
  int *extraout_R11_00;
  int unaff_R14;
  int in_XMM15_Qa;
  int in_XMM15_Qb;
  undefined8 uStack0000000000000008;
  int iStack0000000000000010;
  undefined8 uStack_208;
  undefined4 uStack_200;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_188;
  undefined8 uStack_184;
  undefined4 uStack_17c;
  uint uStack_178;
  uint uStack_170;
  uint uStack_168;
  uint uStack_160;
  uint uStack_158;
  uint uStack_150;
  uint uStack_148;
  uint uStack_140;
  int iStack_138;
  uint uStack_130;
  int iStack_128;
  int iStack_120;
  undefined1 auStack_118 [16];
  undefined2 uStack_108;
  undefined2 uStack_106;
  int iStack_100;
  uint uStack_f8;
  uint uStack_f0;
  int iStack_e8;
  uint uStack_e0;
  uint uStack_d8;
  int iStack_d0;
  uint uStack_c8;
  uint uStack_c0;
  int iStack_b8;
  uint uStack_b0;
  uint uStack_a8;
  int *piStack_a0;
  int iStack_98;
  int iStack_90;
  undefined8 uStack_88;
  int iStack_80;
  undefined8 uStack_78;
  int iStack_70;
  int iStack_68;
  int iStack_60;
  internal_abi_Type *piStack_58;
  undefined8 uStack_50;
  internal_abi_Type *piStack_48;
  undefined8 uStack_40;
  internal_abi_Type *piStack_38;
  undefined8 uStack_30;
  internal_abi_Type *piStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  int iStack_10;

  uStack0000000000000008 = param_1;
  iStack0000000000000010 = param_2;
  while (&uStack_188 <= *(undefined4 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  uStack_88 = uStack0000000000000008;
  iStack_80 = iStack0000000000000010;
  uStack_78 = param_3;
  iStack_70 = in_XMM15_Qb;
  iStack_68 = in_XMM15_Qa;
  iStack_60 = in_XMM15_Qb;
  uVar12 = FUN_14066cbe0(&uStack_88);
  if (iStack_68 != 0) {
    auVar3._8_8_ = iStack_60;
    auVar3._0_8_ = iStack_68;
    auVar3._16_8_ = 0;
    return auVar3 << 0x40;
  }
  uStack_130 = (uint)uVar12;
  iStack_90 = FUN_1400762e0(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Track___Struct_type,0)
  ;
  piVar17 = (int *)FUN_140016c60(&gommo/pkg/assets/r3char::
                                  gommo_pkg_assets_r3char_Clip___Struct_type);
  uVar18 = uStack_130;
  piVar17[2] = uStack_130;
  if (DAT_1444d6c60 != 0) {
    piVar17 = (int *)FUN_14007c580();
    *extraout_R11 = iStack_90;
  }
  *piVar17 = iStack_90;
  iVar19 = 0;
  piStack_a0 = piVar17;
  while( true ) {
    if ((int)uVar18 <= iVar19) {
      if (iStack_68 != 0) {
        auVar7._8_8_ = iStack_60;
        auVar7._0_8_ = iStack_68;
        auVar7._16_8_ = 0;
        return auVar7 << 0x40;
      }
      if (iStack_70 == iStack0000000000000010) {
        return ZEXT824(piVar17);
      }
      uStack_50 = FUN_140071a60(iStack_70);
      piStack_58 = &int___Int_type;
      uStack_40 = FUN_140071a60(iStack0000000000000010);
      piStack_48 = &int___Int_type;
      auVar2 = FUN_140117060("r3char: clip consumed %d bytes of %d",0x24,&piStack_58,2,2);
      auVar6._16_8_ = 0;
      auVar6._0_16_ = auVar2;
      return auVar6 << 0x40;
    }
    iStack_128 = iStack_70;
    iStack_138 = iVar19;
    cVar11 = FUN_14066cac0(&uStack_88,0x8c);
    if (cVar11 == '\0') {
      uStack_30 = FUN_140071a60(iStack_138);
      piStack_38 = &int___Int_type;
      uStack_20 = FUN_140071a60(uStack_130);
      piStack_28 = &int___Int_type;
      uStack_18 = 0;
      if (iStack_68 != 0) {
        uStack_18 = *(undefined8 *)(iStack_68 + 8);
      }
      iStack_10 = iStack_60;
      auVar2 = FUN_140117060("r3char: clip track %d of %d: %w",0x1f,&piStack_38,3,3);
      auVar5._16_8_ = 0;
      auVar5._0_16_ = auVar2;
      return auVar5 << 0x40;
    }
    FUN_14066cda0(&uStack_88,100);
    auStack_118 = FUN_14007cc66();
    uStack_108 = FUN_14066cbe0(&uStack_88);
    uStack_106 = FUN_14066cbe0(&uStack_88);
    iStack_70 = iStack_128 + 0x8c;
    uVar12 = FUN_14066cbe0(&uStack_88);
    uStack_168 = (uint)uVar12;
    cVar11 = FUN_14066cac0(&uStack_88,uStack_168 * 0x14);
    if (cVar11 == '\0') {
      auVar4._8_8_ = iStack_60;
      auVar4._0_8_ = iStack_68;
      auVar4._16_8_ = 0;
      return auVar4 << 0x40;
    }
    iStack_100 = FUN_1400762e0(&gommo/pkg/assets/r3char::
                                gommo_pkg_assets_r3char_RotKey___Struct_type,uStack_168,uStack_168);
    uStack_f8 = uStack_168;
    uStack_f0 = uStack_168;
    uVar18 = 0;
    while ((int)uVar18 < (int)uStack_168) {
      uStack_140 = uVar18;
      uVar13 = FUN_14066cc80(&uStack_88);
      uVar14 = FUN_14066cc80(&uStack_88);
      uVar15 = FUN_14066cc80(&uStack_88);
      uVar16 = FUN_14066cc80(&uStack_88);
      uStack_188 = FUN_14066cc80(&uStack_88);
      if (uStack_f8 <= uStack_140) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940();
      }
      puVar1 = (undefined8 *)(iStack_100 + uStack_140 * 0x14);
      *puVar1 = CONCAT44(uVar14,uVar13);
      *(undefined4 *)((int)puVar1 + 4) = uVar14;
      *(undefined4 *)(puVar1 + 1) = uVar15;
      *(undefined4 *)((int)puVar1 + 0xc) = uVar16;
      *(undefined4 *)(puVar1 + 2) = uStack_188;
      uVar18 = uStack_140 + 1;
    }
    uVar12 = FUN_14066cbe0(&uStack_88);
    uStack_178 = (uint)uVar12;
    cVar11 = FUN_14066cac0(&uStack_88,uStack_178 << 4);
    if (cVar11 == '\0') {
      auVar8._8_8_ = iStack_60;
      auVar8._0_8_ = iStack_68;
      auVar8._16_8_ = 0;
      return auVar8 << 0x40;
    }
    iStack_e8 = FUN_1400762e0(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_VecKey___Struct_type
                              ,uStack_178,uStack_178);
    uStack_e0 = uStack_178;
    uStack_d8 = uStack_178;
    uVar18 = 0;
    while ((int)uVar18 < (int)uStack_178) {
      uStack_148 = uVar18;
      FUN_14066cd20(&uStack_88);
      uStack_184 = uStack_208;
      uStack_17c = uStack_200;
      uVar13 = FUN_14066cc80(&uStack_88);
      if (uStack_e0 <= uStack_148) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940();
      }
      puVar20 = (undefined4 *)(iStack_e8 + uStack_148 * 0x10);
      uStack_1a8 = (undefined4)uStack_184;
      uStack_1a4 = (undefined4)((uint)uStack_184 >> 0x20);
      *puVar20 = uStack_1a8;
      puVar20[1] = uStack_1a4;
      puVar20[2] = uStack_17c;
      puVar20[3] = uVar13;
      uVar18 = uStack_148 + 1;
    }
    uVar12 = FUN_14066cbe0(&uStack_88);
    uStack_170 = (uint)uVar12;
    cVar11 = FUN_14066cac0(&uStack_88,uStack_170 << 4);
    if (cVar11 == '\0') break;
    iStack_d0 = FUN_1400762e0(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_VecKey___Struct_type
                              ,uStack_170,uStack_170);
    uStack_c8 = uStack_170;
    uStack_c0 = uStack_170;
    uVar18 = 0;
    while ((int)uVar18 < (int)uStack_170) {
      uStack_150 = uVar18;
      FUN_14066cd20(&uStack_88);
      uStack_184 = uStack_208;
      uStack_17c = uStack_200;
      uVar13 = FUN_14066cc80(&uStack_88);
      if (uStack_c8 <= uStack_150) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940();
      }
      puVar20 = (undefined4 *)(iStack_d0 + uStack_150 * 0x10);
      uStack_1b8 = (undefined4)uStack_184;
      uStack_1b4 = (undefined4)((uint)uStack_184 >> 0x20);
      *puVar20 = uStack_1b8;
      puVar20[1] = uStack_1b4;
      puVar20[2] = uStack_17c;
      puVar20[3] = uVar13;
      uVar18 = uStack_150 + 1;
    }
    uVar12 = FUN_14066cbe0(&uStack_88);
    uStack_160 = (uint)uVar12;
    cVar11 = FUN_14066cac0(&uStack_88,uStack_160 << 3);
    if (cVar11 == '\0') {
      auVar10._8_8_ = iStack_60;
      auVar10._0_8_ = iStack_68;
      auVar10._16_8_ = 0;
      return auVar10 << 0x40;
    }
    iStack_b8 = FUN_1400762e0(&gommo/pkg/assets/r3char::
                               gommo_pkg_assets_r3char_AlphaKey___Struct_type,uStack_160,uStack_160)
    ;
    uStack_b0 = uStack_160;
    uStack_a8 = uStack_160;
    uVar18 = 0;
    while ((int)uVar18 < (int)uStack_160) {
      uStack_158 = uVar18;
      uVar13 = FUN_14066cc80(&uStack_88);
      uVar14 = FUN_14066cc80(&uStack_88);
      if (uStack_b0 <= uStack_158) {
                    /* WARNING: Subroutine does not return */
        FUN_14007c940(uStack_158);
      }
      *(undefined4 *)(iStack_b8 + uStack_158 * 8) = uVar13;
      *(undefined4 *)(iStack_b8 + 4 + uStack_158 * 8) = uVar14;
      uVar18 = uStack_158 + 1;
    }
    uVar18 = piStack_a0[2];
    uVar22 = piStack_a0[1] + 1;
    iVar19 = *piStack_a0;
    if (uVar18 < uVar22) {
      FUN_1400763c0(iVar19,uVar22,uVar18,1,
                    &gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Track___Struct_type);
      piVar17 = piStack_a0;
      piStack_a0[2] = extraout_RCX;
      iVar19 = extraout_RAX;
      uVar18 = extraout_RCX;
      uVar22 = extraout_RBX;
      if (DAT_1444d6c60 != 0) {
        FUN_14007c5a0();
        *extraout_R11_00 = extraout_RAX_00;
        extraout_R11_00[1] = extraout_R8;
        iVar19 = extraout_RAX_00;
        uVar18 = extraout_RCX_00;
        uVar22 = extraout_RBX_00;
      }
      *piVar17 = iVar19;
    }
    piStack_a0[1] = uVar22;
    iVar23 = uVar22 * 0x78;
    iVar21 = iVar23 + iVar19 + -0x78;
    if (DAT_1444d6c60 != 0) {
      iStack_120 = iVar23;
      iStack_98 = iVar19;
      FUN_140017560(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Track___Struct_type,iVar21,
                    auStack_118);
      uVar18 = extraout_RCX_01;
      iVar19 = iStack_98;
      iVar21 = extraout_RBX_01;
      iVar23 = iStack_120;
    }
    *(undefined8 *)(iVar23 + -0x78 + iVar19) = auStack_118._0_8_;
    piVar17 = (int *)FUN_14007cfbe(piStack_a0,iVar21,uVar18,iVar23 + iVar19 + -0x70,auStack_118 + 8)
    ;
    iVar19 = iStack_138 + 1;
    uVar18 = uStack_130;
  }
  auVar9._8_8_ = iStack_60;
  auVar9._0_8_ = iStack_68;
  auVar9._16_8_ = 0;
  return auVar9 << 0x40;
}
