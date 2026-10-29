/* Generated pseudocode, NOT original Go source.
 * Go symbol: gommo/pkg/assets/rfdata.Decode
 * VA: 0x140940b40
 * Ghidra type recovery was incomplete; inferred pointer/int and Go ABI types may be wrong.
 * Calls recognized from retained Go metadata:
 * FUN_14007a680: runtime.morestack_noctxt
 * FUN_140940b40: gommo/pkg/assets/rfdata.Decode
 * FUN_140940de0: gommo/pkg/assets/rfdata.parseEDFLayout
 * FUN_1409410c0: gommo/pkg/assets/rfdata.DecryptEDF
 */
undefined1  [40] FUN_140940b40(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 extraout_RAX;
  undefined8 extraout_RCX;
  undefined8 extraout_RBX;
  undefined1 auVar1 [40];
  undefined8 extraout_RSI;
  int extraout_RDI;
  undefined8 extraout_RDI_00;
  int unaff_R14;
  undefined1 uStack0000000000000000;
  undefined8 uStack0000000000000008;
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;

  uStack0000000000000008 = param_1;
  uStack0000000000000018 = param_3;
  uStack0000000000000010 = param_2;
  while (&uStack0000000000000000 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    FUN_14007a680();
  }
  FUN_140940de0();
  if (extraout_RDI == 0) {
    FUN_1409410c0(uStack0000000000000008,uStack0000000000000010,uStack0000000000000018);
    auVar1._8_8_ = extraout_RBX;
    auVar1._0_8_ = extraout_RAX;
    auVar1._16_8_ = extraout_RCX;
    auVar1._24_8_ = extraout_RDI_00;
    auVar1._32_8_ = extraout_RSI;
    return auVar1;
  }
  return ZEXT2440(CONCAT816(uStack0000000000000018,
                            CONCAT88(uStack0000000000000010,uStack0000000000000008)));
}
