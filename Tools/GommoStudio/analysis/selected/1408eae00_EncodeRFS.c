/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/rfpack.EncodeRFS
 * VA: 0x1408eae00
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140071a60: runtime.convT64
 * FUN_1400762e0: runtime.makeslice
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007c9c0: runtime.panicSliceAcap
 * FUN_14007ca00: runtime.panicSliceB
 * FUN_14007d340: runtime.memmove
 * FUN_140117060: fmt.Errorf
 * FUN_1405af920: gommo/pkg/assets/fixstr.Field.Put
 * FUN_1408eae00: gommo/pkg/assets/rfpack.EncodeRFS
 */
undefined1  [40] FUN_1408eae00(undefined8 *param_1,int param_2)

{
  int extraout_RAX;
  undefined4 *extraout_RAX_00;
  undefined8 *puVar1;
  undefined4 *puVar2;
  undefined4 *extraout_RAX_01;
  uint extraout_RCX;
  uint extraout_RCX_01;
  int iVar5;
  int extraout_RBX;
  uint extraout_RBX_01;
  undefined1 auVar3 [40];
  int extraout_RCX_00;
  uint extraout_RBX_00;
  uint uVar6;
  undefined1 auVar4 [40];
  uint uVar7;
  int extraout_R8;
  uint uVar8;
  undefined8 *extraout_R9;
  int extraout_R9_00;
  undefined8 *puVar9;
  undefined8 uVar10;
  int iVar11;
  int extraout_R11;
  undefined8 *puVar12;
  int unaff_R14;
  uint uVar13;
  uint uVar14;
  undefined1 auVar15 [16];
  undefined8 *puStack0000000000000008;
  uint uStack_128;
  int iStack_120;
  undefined1 *puStack_118;
  undefined4 *puStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  int iStack_f0;
  undefined1 auStack_e0 [64];
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 *puStack_90;
  undefined8 *puStack_88;
  internal_abi_Type *piStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined1 auStack_68 [8];
  undefined8 uStack_60;
  uint uStack_58;

  while (puStack0000000000000008 = param_1, &uStack_128 <= *(uint **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
    param_1 = puStack0000000000000008;
  }
  iVar5 = param_2 * 0x40;
  uStack_128 = iVar5 + 4;
  iVar11 = 0;
  uVar8 = uStack_128;
  puStack_88 = param_1;
  while (iVar11 < param_2) {
    uStack_70 = *param_1;
    FUN_14007cfcc();
    param_1 = (undefined8 *)(extraout_RAX + 0x68);
    uVar8 = extraout_R8 + uStack_58;
    uStack_128 = extraout_RCX;
    param_2 = extraout_RBX;
    puStack_88 = extraout_R9;
    iVar11 = extraout_R11 + 1;
  }
  if (0xffffffff < uVar8) {
    uStack_78 = FUN_140071a60(uVar8);
    piStack_80 = &int___Int_type;
    auVar15 = FUN_140117060("rfs: %d bytes overflow the 32-bit offsets",0x29,&piStack_80,1,1);
    auVar3._0_24_ = ZEXT824(0);
    auVar3._24_8_ = auVar15._0_8_;
    auVar3._32_8_ = auVar15._8_8_;
    return auVar3;
  }
  iStack_120 = iVar5;
  puStack_90 = (undefined8 *)FUN_1400762e0(&uint8___Uint8_type,uStack_128,uVar8);
  if (uStack_128 < 4) {
                    /* WARNING: Subroutine does not return */
    FUN_14007c940(3);
  }
  *(sdword *)puStack_90 = (sdword)param_2;
  iVar11 = 0;
  uVar14 = uStack_128;
  puVar12 = puStack_88;
  while( true ) {
    if (param_2 <= iVar11) {
      uVar14 = uStack_128;
      puVar12 = puStack_88;
      for (iStack_120 = 0; iStack_120 < param_2; iStack_120 = iStack_120 + 1) {
        uStack_70 = *puVar12;
        puVar2 = (undefined4 *)puStack_90;
        puStack_90 = puVar12;
        auVar15 = FUN_14007cfcc(puVar2,uVar14,iStack_120,auStack_68,puVar12 + 1);
        puVar2 = auVar15._0_8_;
        uVar14 = uStack_58 + auVar15._8_8_;
        uVar7 = uStack_58;
        uVar10 = uStack_60;
        if (uVar8 < uVar14) {
          uStack_a0 = uStack_60;
          uStack_128 = uStack_58;
          FUN_1400763c0(puVar2,uVar14,uVar8,uStack_58,&uint8___Uint8_type);
          puVar2 = extraout_RAX_01;
          uVar8 = extraout_RCX_01;
          uVar7 = uStack_128;
          uVar14 = extraout_RBX_01;
          uVar10 = uStack_a0;
        }
        puStack_110 = puVar2;
        FUN_14007d340((int)puVar2 + auVar15._8_8_,uVar10,uVar7);
        puVar12 = puStack_90 + 0xd;
        puStack_90 = (undefined8 *)puStack_110;
      }
      return ZEXT2440(CONCAT816(uVar8,CONCAT88(uVar14,puStack_90)));
    }
    uStack_70 = *puVar12;
    puVar9 = puStack_88;
    iVar5 = iStack_120;
    FUN_14007cfcc(puStack_90,uStack_128,uVar14,auStack_68,puVar12 + 1,puVar12 + 1,iVar11);
    uStack_108 = uStack_70;
    FUN_14007cfcc();
    uVar14 = extraout_R9_00 * 0x40 + 4;
    if (extraout_RBX_00 < uVar14) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(uVar14,extraout_RBX_00,extraout_RBX_00);
    }
    uVar13 = iVar5 + extraout_R9_00 * -0x40;
    iVar11 = uVar8 + extraout_R9_00 * -0x40;
    uVar7 = iVar11 - 4;
    puStack_118 = (undefined1 *)(((int)-uVar7 >> 0x3f & uVar14) + (int)extraout_RAX_00);
    uVar14 = uVar13;
    if (0x38 < (int)uVar13) {
      uVar14 = 0x38;
    }
    puVar1 = (undefined8 *)extraout_RAX_00;
    uVar6 = extraout_RBX_00;
    puStack_98 = puVar12;
    if (auStack_e0 != puStack_118) {
      FUN_14007d340(puStack_118,auStack_e0,uVar14,puStack_118,extraout_R9_00,iVar5,puVar9);
      puVar1 = puStack_90;
      uVar6 = uStack_128;
      iVar5 = iStack_120;
      puVar9 = puStack_88;
    }
    if (uVar7 < 0x38) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c9c0(puVar1,uVar6,0x38,puStack_118,extraout_R9_00,iVar5,puVar9,iVar11);
    }
    auVar15 = FUN_1405af920(DAT_144172870,DAT_144172878,PTR_PTR_144172880,puStack_118,0x38,uVar7,
                            uStack_108,uStack_100);
    uStack_78 = auVar15._8_8_;
    iVar5 = auVar15._0_8_;
    if (iVar5 != 0) {
      piStack_80 = (internal_abi_Type *)0x0;
      if (iVar5 != 0) {
        piStack_80 = *(internal_abi_Type **)(iVar5 + 8);
      }
      auVar15 = FUN_140117060("rfs: name: %w",0xd,&piStack_80,1,1);
      auVar4._0_24_ = ZEXT824(0);
      auVar4._24_8_ = auVar15._0_8_;
      auVar4._32_8_ = auVar15._8_8_;
      return auVar4;
    }
    if (uVar13 < 0x38) break;
    if (uVar13 - 0x38 < 4) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(3,uStack_78,uVar13 - 0x38);
    }
    *(sdword *)(puStack_118 + ((dword)(-(iVar11 + -0x3c) >> 0x3f) & 0x38)) = (sdword)extraout_RCX_00
    ;
    if (uVar13 < 0x3c) {
                    /* WARNING: Subroutine does not return */
      FUN_14007ca00(0x3c);
    }
    if (uVar13 - 0x3c < 4) {
                    /* WARNING: Subroutine does not return */
      FUN_14007c940(3);
    }
    *(sdword *)(puStack_118 + ((dword)(-(iVar11 + -0x40) >> 0x3f) & 0x3c)) = (sdword)iStack_f0;
    puVar12 = puStack_98 + 0xd;
    uVar14 = extraout_RCX_00 + iStack_f0;
    iVar11 = extraout_R9_00 + 1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_14007ca00(0x38);
}
