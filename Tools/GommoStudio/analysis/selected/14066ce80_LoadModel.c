/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/r3char.LoadModel
 * VA: 0x14066ce80
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_1400037e0: runtime.memequal
 * FUN_140016c60: runtime.newobject
 * FUN_140017560: runtime.wbMove
 * FUN_140071a60: runtime.convT64
 * FUN_1400762e0: runtime.makeslice
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c580: runtime.gcWriteBarrier1
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_140117060: fmt.Errorf
 * FUN_14066cbe0: gommo/pkg/assets/r3char.(*reader).u16
 * FUN_14066ce80: gommo/pkg/assets/r3char.LoadModel
 * FUN_14066d5a0: gommo/pkg/assets/r3char.(*Model).resolveAttachments
 * FUN_14066db40: gommo/pkg/assets/r3char.readMesh
 * FUN_14066dde0: gommo/pkg/assets/r3char.readPrototype
 * FUN_14066e360: gommo/pkg/assets/r3char.readMesh08Body
 */
undefined1  [24] FUN_14066ce80(int param_1,uint param_2,int param_3)

{
  undefined1 auVar1 [24];
  undefined1 auVar2 [24];
  undefined1 auVar3 [24];
  undefined1 auVar4 [24];
  int *piVar5;
  ushort uVar6;
  int iVar7;
  int extraout_RAX;
  int extraout_RAX_00;
  undefined8 extraout_RCX;
  uint extraout_RCX_00;
  uint extraout_RCX_01;
  uint uVar8;
  uint extraout_RCX_02;
  int iVar9;
  undefined8 extraout_RBX;
  uint uVar10;
  uint extraout_RBX_00;
  uint extraout_RBX_01;
  int extraout_RBX_02;
  undefined8 extraout_RSI;
  undefined8 extraout_RDI;
  int extraout_R8;
  int iVar11;
  int *extraout_R11;
  int *extraout_R11_00;
  int unaff_R14;
  int in_XMM15_Qa;
  uint in_XMM15_Qb;
  undefined1 auVar12 [16];
  int iStack0000000000000008;
  undefined8 uStack_980;
  undefined1 auStack_978 [120];
  undefined1 auStack_900 [424];
  undefined8 uStack_758;
  char cStack_521;
  int iStack_520;
  int iStack_518;
  uint uStack_510;
  int iStack_508;
  uint uStack_500;
  undefined8 uStack_4f8;
  undefined1 auStack_4f0 [544];
  int *piStack_2d0;
  undefined8 uStack_2c8;
  int iStack_2c0;
  int iStack_2b8;
  int iStack_2b0;
  uint uStack_2a8;
  int iStack_2a0;
  uint uStack_298;
  int iStack_290;
  uint uStack_288;
  internal_abi_Type *piStack_280;
  undefined8 uStack_278;
  internal_abi_Type *piStack_270;
  undefined8 uStack_268;
  internal_abi_Type *piStack_260;
  undefined8 uStack_258;
  internal_abi_Type *piStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined1 auStack_228 [544];

  iStack0000000000000008 = param_1;
  while (auStack_900 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  if ((int)param_2 < 6) {
    cStack_521 = '\0';
  }
  else {
    cStack_521 = FUN_1400037e0(iStack0000000000000008,"MESH08",6);
  }
  iStack_2b0 = iStack0000000000000008;
  if (cStack_521 != '\0') {
    if (param_2 < 6) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(6,param_2,param_2);
    }
    param_3 = param_3 + -6;
    iStack_2b0 = iStack0000000000000008 + (uint)((dword)(-param_3 >> 0x3f) & 6);
    param_2 = param_2 - 6;
  }
  uStack_500 = param_2;
  uStack_2a8 = param_2;
  iStack_2a0 = param_3;
  uStack_298 = in_XMM15_Qb;
  iStack_290 = in_XMM15_Qa;
  uStack_288 = in_XMM15_Qb;
  uVar6 = FUN_14066cbe0(&iStack_2b0);
  if (iStack_290 != 0) {
    auVar1._8_8_ = uStack_288;
    auVar1._0_8_ = iStack_290;
    auVar1._16_8_ = 0;
    return auVar1 << 0x40;
  }
  uStack_510 = (uint)uVar6;
  iStack_2b8 = FUN_1400762e0(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Mesh___Struct_type,0)
  ;
  piStack_2d0 = (int *)FUN_140016c60(&DAT_14257f680);
  uVar8 = uStack_510;
  piStack_2d0[2] = uStack_510;
  if (DAT_1444d6c60 != 0) {
    piStack_2d0 = (int *)FUN_14007c580();
    *extraout_R11 = iStack_2b8;
  }
  *piStack_2d0 = iStack_2b8;
  iVar7 = 0;
  while (iVar7 < (int)uVar8) {
    iStack_520 = iVar7;
    FUN_14007cbca();
    if (cStack_521 == '\0') {
      FUN_14007cbca();
      FUN_14066db40(&iStack_2b0);
      uStack_230 = uStack_980;
      FUN_14007ce44();
      uStack_4f8 = uStack_230;
      auVar12 = FUN_14007ce44();
    }
    else {
      FUN_14007cbca();
      FUN_14066dde0(&iStack_2b0);
      uStack_230 = uStack_980;
      FUN_14007ce44(extraout_RDI,extraout_RBX,extraout_RSI,auStack_228,auStack_978);
      uStack_4f8 = uStack_230;
      iVar7 = FUN_14007ce44();
      auVar12._8_8_ = extraout_RCX;
      auVar12._0_8_ = iVar7;
      if (iVar7 == 0) {
        FUN_14007cbca();
        uStack_980 = uStack_4f8;
        FUN_14007ce44();
        FUN_14066e360(&iStack_2b0);
        uStack_230 = uStack_758;
        FUN_14007ce44();
        uStack_4f8 = uStack_230;
        auVar12 = FUN_14007ce44();
      }
    }
    uStack_2c8 = auVar12._8_8_;
    iStack_518 = auVar12._0_8_;
    if (iStack_518 != 0) {
      uStack_258 = FUN_140071a60(iStack_520);
      piStack_260 = &int___Int_type;
      uStack_248 = FUN_140071a60(uStack_510);
      piStack_250 = &int___Int_type;
      if (iStack_518 == 0) {
        uStack_240 = 0;
      }
      else {
        uStack_240 = *(undefined8 *)(iStack_518 + 8);
      }
      uStack_238 = uStack_2c8;
      auVar12 = FUN_140117060("r3char: mesh %d of %d: %w",0x19,&piStack_260,3,3);
      auVar2._16_8_ = 0;
      auVar2._0_16_ = auVar12;
      return auVar2 << 0x40;
    }
    uVar8 = piStack_2d0[2];
    uVar10 = piStack_2d0[1] + 1;
    iVar7 = *piStack_2d0;
    if (uVar8 < uVar10) {
      FUN_1400763c0(iVar7,uVar10,uVar8,1,
                    &gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Mesh___Struct_type);
      piVar5 = piStack_2d0;
      piStack_2d0[2] = extraout_RCX_00;
      iVar7 = extraout_RAX;
      uVar8 = extraout_RCX_00;
      uVar10 = extraout_RBX_00;
      if (DAT_1444d6c60 != 0) {
        FUN_14007c5a0();
        *extraout_R11_00 = extraout_RAX_00;
        extraout_R11_00[1] = extraout_R8;
        iVar7 = extraout_RAX_00;
        uVar8 = extraout_RCX_01;
        uVar10 = extraout_RBX_01;
      }
      *piVar5 = iVar7;
    }
    piStack_2d0[1] = uVar10;
    iVar11 = uVar10 * 0x228;
    iVar9 = iVar11 + iVar7 + -0x228;
    if (DAT_1444d6c60 != 0) {
      iStack_508 = iVar11;
      iStack_2c0 = iVar7;
      FUN_140017560(&gommo/pkg/assets/r3char::gommo_pkg_assets_r3char_Mesh___Struct_type,iVar9,
                    &uStack_4f8);
      uVar8 = extraout_RCX_02;
      iVar7 = iStack_2c0;
      iVar9 = extraout_RBX_02;
      iVar11 = iStack_508;
    }
    *(undefined8 *)(iVar11 + -0x228 + iVar7) = uStack_4f8;
    FUN_14007ce44(piStack_2d0,iVar9,uVar8,iVar11 + iVar7 + -0x220,auStack_4f0);
    uVar8 = uStack_510;
    iVar7 = iStack_520 + 1;
  }
  if (iStack_290 != 0) {
    auVar4._8_8_ = uStack_288;
    auVar4._0_8_ = iStack_290;
    auVar4._16_8_ = 0;
    return auVar4 << 0x40;
  }
  if (uStack_298 == uStack_500) {
    FUN_14066d5a0();
    return ZEXT824(piStack_2d0);
  }
  uStack_278 = FUN_140071a60(uStack_298);
  piStack_280 = &int___Int_type;
  uStack_268 = FUN_140071a60(uStack_500);
  piStack_270 = &int___Int_type;
  auVar12 = FUN_140117060("r3char: consumed %d bytes of %d",0x1f,&piStack_280,2,2);
  auVar3._16_8_ = 0;
  auVar3._0_16_ = auVar12;
  return auVar3 << 0x40;
}
