/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/r3char.EncodeModel
 * VA: 0x140669d20
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_140071a60: runtime.convT64
 * FUN_140071ae0: runtime.convTstring
 * FUN_1400763c0: runtime.growslice
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_14007c940: runtime.panicIndex
 * FUN_14007d340: runtime.memmove
 * FUN_140117060: fmt.Errorf
 * FUN_140669d20: gommo/pkg/assets/r3char.EncodeModel
 * FUN_14066a020: gommo/pkg/assets/r3char.encodeMesh
 */
undefined1  [16] FUN_140669d20(int *param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined8 uVar3;
  undefined2 *extraout_RAX;
  uint extraout_RCX;
  uint uVar4;
  uint extraout_RCX_00;
  int iVar5;
  uint uVar6;
  uint extraout_RBX;
  uint uVar7;
  undefined8 extraout_RSI;
  int extraout_RDI;
  uint uVar8;
  int unaff_R14;
  undefined1 auVar9 [16];
  undefined8 uStack_60;
  undefined8 uStack_58;
  int iStack_50;
  internal_abi_Type *piStack_48;
  undefined8 uStack_40;
  internal_abi_Type *piStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  internal_abi_Type *piStack_18;
  undefined8 uStack_10;

  while (&uStack_60 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  iVar1 = param_1[1];
  if (0xffff < iVar1) {
    uStack_10 = FUN_140071a60(iVar1);
    piStack_18 = &int___Int_type;
    FUN_140117060("r3char: %d meshes, the count is a u16",0x25,&piStack_18,1,1);
    return ZEXT816(0);
  }
  puVar2 = (undefined2 *)FUN_1400763c0(0,2,0,2,&uint8___Uint8_type);
  *puVar2 = (short)iVar1;
  iVar1 = param_1[1];
  uVar6 = 0;
  uVar4 = extraout_RCX;
  uVar7 = 2;
  while( true ) {
    if (iVar1 <= (int)uVar6) {
      auVar9._8_8_ = uVar7;
      auVar9._0_8_ = puVar2;
      return auVar9;
    }
    if ((uint)param_1[1] <= uVar6) break;
    iStack_50 = *param_1;
    iVar5 = uVar6 * 0x228;
    auVar9 = FUN_14066a020(iStack_50 + iVar5);
    auVar9._8_8_ = auVar9._8_8_;
    if (extraout_RDI != 0) {
      uStack_60 = extraout_RSI;
      uStack_40 = FUN_140071a60(uVar6);
      piStack_48 = &int___Int_type;
      uStack_30 = FUN_140071ae0(*(undefined8 *)(iStack_50 + iVar5),
                                *(undefined8 *)(iStack_50 + 8 + iVar5));
      piStack_38 = &string___String_type;
      if (extraout_RDI == 0) {
        uStack_28 = 0;
      }
      else {
        uStack_28 = *(undefined8 *)(extraout_RDI + 8);
      }
      uStack_20 = uStack_60;
      FUN_140117060("r3char: mesh %d %q: %w",0x16,&piStack_48,3,3);
      return ZEXT816(0);
    }
    uVar8 = uVar7 + auVar9._8_8_;
    if (uVar4 < uVar8) {
      uStack_58 = auVar9._0_8_;
      FUN_1400763c0(puVar2,uVar8,uVar4,auVar9._8_8_,&uint8___Uint8_type);
      uVar3 = uStack_58;
      uVar4 = extraout_RCX_00;
      puVar2 = extraout_RAX;
      uVar8 = extraout_RBX;
    }
    else {
      uVar3 = auVar9._0_8_;
    }
    FUN_14007d340(uVar7 + (int)puVar2,uVar3,auVar9._8_8_);
    uVar6 = uVar6 + 1;
    uVar7 = uVar8;
  }
                    /* WARNING: Subroutine does not return */
  FUN_14007c940(uVar6,uVar6,param_1[1]);
}
