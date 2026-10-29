/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/rfpack.ReadRFSEntries
 * VA: 0x1408ea940
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140013220: runtime.convT32
 * FUN_140071a60: runtime.convT64
 * FUN_1400762e0: runtime.makeslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c5a0: runtime.gcWriteBarrier2
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_14007d340: runtime.memmove
 * FUN_140117060: fmt.Errorf
 * FUN_1405afae0: gommo/pkg/assets/fixstr.CString
 * FUN_1408ea940: gommo/pkg/assets/rfpack.ReadRFSEntries
 */
undefined1  [16] FUN_1408ea940(dword *param_1,uint param_2,uint param_3)

{
  dword dVar1;
  dword dVar2;
  dword dVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  dword *pdVar7;
  uint uVar8;
  uint extraout_RCX;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int extraout_RSI;
  int extraout_RSI_00;
  uint uVar13;
  uint extraout_R8;
  uint extraout_R8_00;
  undefined8 extraout_R9;
  int iVar14;
  int extraout_R9_00;
  uint extraout_R10;
  undefined8 *extraout_R11;
  int *extraout_R11_00;
  int unaff_R14;
  undefined1 auVar15 [16];
  dword *pdStack0000000000000008;
  internal_abi_Type *piStack_78;
  undefined8 uStack_70;
  internal_abi_Type *piStack_68;
  undefined8 uStack_60;
  internal_abi_Type *piStack_58;
  undefined8 uStack_50;
  internal_abi_Type *piStack_48;
  undefined8 uStack_40;
  internal_abi_Type *piStack_38;
  undefined8 uStack_30;
  internal_abi_Type *piStack_28;
  undefined8 uStack_20;
  internal_abi_Type *piStack_18;
  undefined8 uStack_10;

  pdStack0000000000000008 = param_1;
  while (&piStack_58 <= *(internal_abi_Type ***)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  if ((int)param_2 < 4) {
    uStack_10 = FUN_140071a60(param_2);
    piStack_18 = &int___Int_type;
    FUN_140117060("rfs: %d bytes",0xd,&piStack_18,1,1);
    return ZEXT816(0);
  }
  dVar1 = *pdStack0000000000000008;
  uVar9 = (uint)dVar1;
  if ((int)param_2 < (int)(uVar9 * 0x40 + 4)) {
    uStack_30 = FUN_140071a60(uVar9);
    piStack_38 = &int___Int_type;
    uStack_20 = FUN_140071a60(param_2);
    piStack_28 = &int___Int_type;
    FUN_140117060("rfs: directory of %d does not fit in %d bytes",0x2d,&piStack_38,2,2);
    return ZEXT816(0);
  }
  iVar4 = FUN_1400762e0(&gommo/pkg/assets/rfpack::gommo_pkg_assets_rfpack_RFSEntry___Struct_type,
                        uVar9,uVar9);
  iVar11 = 0;
  iVar5 = iVar4;
  uVar8 = param_3;
  pdVar7 = pdStack0000000000000008;
  while( true ) {
    if ((int)uVar9 <= iVar11) {
      auVar15._8_4_ = dVar1;
      auVar15._0_8_ = iVar5;
      auVar15._12_4_ = 0;
      return auVar15;
    }
    uVar13 = iVar11 * 0x40 + 4;
    if (param_2 < uVar13) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar13,iVar11 * 0x40,param_2);
    }
    iVar12 = uVar8 + iVar11 * -0x40;
    iVar10 = param_2 + iVar11 * -0x40;
    uVar8 = iVar10 - 4;
    iVar14 = (int)pdVar7 + (-(iVar12 + -4) >> 0x3f & uVar13);
    if (uVar8 < 0x38) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(0x38,iVar14,uVar8);
    }
    if (iVar10 - 0x3cU < 4) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(3,iVar14,iVar10 - 0x3cU);
    }
    dVar2 = *(dword *)((uint)((dword)(-(iVar12 + -0x3c) >> 0x3f) & 0x38) + iVar14);
    if (uVar8 < 0x3c) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(0x3c,iVar14,uVar8);
    }
    if (iVar10 - 0x40U < 4) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(3,iVar14,iVar10 - 0x40U);
    }
    dVar3 = *(dword *)((uint)((dword)(-(iVar12 + -0x40) >> 0x3f) & 0x3c) + iVar14);
    if (param_2 < (uint)dVar2 + (uint)dVar3) {
      uStack_70 = FUN_140071a60(iVar11);
      piStack_78 = &int___Int_type;
      uStack_60 = FUN_140013220(dVar2);
      piStack_68 = &uint32___Uint32_type;
      uStack_50 = FUN_140013220(dVar3);
      piStack_58 = &uint32___Uint32_type;
      uStack_40 = FUN_140071a60(param_2);
      piStack_48 = &int___Int_type;
      FUN_140117060("rfs: entry %d at %d+%d exceeds %d bytes",0x27,&piStack_78,4,4);
      return ZEXT816(0);
    }
    iVar10 = iVar11 * 0x68;
    iVar5 = iVar5 + iVar10 + 0x28;
    if (iVar5 != iVar14) {
      FUN_14007d340(iVar5,iVar14,0x38);
    }
    auVar15 = FUN_1405afae0(iVar14,0x38,iVar12 + -4);
    uVar6 = auVar15._0_8_;
    *(int *)(iVar4 + 8 + iVar10) = auVar15._8_8_;
    uVar13 = (uint)dVar2;
    uVar8 = (uint)(dword)(dVar2 + dVar3);
    iVar5 = iVar4;
    if (DAT_1444d6c60 != 0) {
      uVar6 = FUN_14007c5a0();
      *extraout_R11 = uVar6;
      extraout_R11[1] = extraout_R9;
      uVar8 = extraout_RCX;
      iVar5 = extraout_RSI;
      uVar13 = extraout_R8;
    }
    *(undefined8 *)(iVar5 + iVar10) = uVar6;
    if (param_3 < uVar8) break;
    if (uVar8 < uVar13) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar13 & 0xffffffff);
    }
    *(uint *)(iVar5 + 0x18 + iVar10) = uVar8 - uVar13;
    *(uint *)(iVar5 + 0x20 + iVar10) = param_3 - uVar13;
    iVar14 = ((int)-(param_3 - uVar13) >> 0x3f & uVar13) + (int)pdStack0000000000000008;
    uVar8 = param_3;
    pdVar7 = pdStack0000000000000008;
    if (DAT_1444d6c60 != 0) {
      iVar5 = *(int *)(iVar5 + 0x10 + iVar10);
      pdVar7 = (dword *)FUN_14007c5a0(pdStack0000000000000008);
      *extraout_R11_00 = extraout_R9_00;
      extraout_R11_00[1] = iVar5;
      iVar5 = extraout_RSI_00;
      uVar13 = extraout_R8_00;
      iVar14 = extraout_R9_00;
      uVar8 = extraout_R10;
    }
    *(int *)(iVar5 + 0x10 + iVar10) = iVar14;
    *(sdword *)(iVar5 + 0x60 + iVar10) = (sdword)uVar13;
    iVar11 = iVar11 + 1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_14007c9c0();
}
