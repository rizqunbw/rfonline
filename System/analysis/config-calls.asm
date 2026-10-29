; Static objdump excerpts, x86 Intel syntax. Input SHA-256: 951e1056875c27f717bfb62d25ffc68d36337416e16d0b7ccc0f7c42b534d2c6


rf_online.bin:     file format pei-i386


Disassembly of section .text:

005286a0 <.text+0x1276a0>:
  5286a0:	55                   	push   ebp
  5286a1:	8b ec                	mov    ebp,esp
  5286a3:	83 ec 70             	sub    esp,0x70
  5286a6:	a1 dc 2e c0 00       	mov    eax,ds:0xc02edc
  5286ab:	33 c5                	xor    eax,ebp
  5286ad:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  5286b0:	53                   	push   ebx
  5286b1:	56                   	push   esi
  5286b2:	57                   	push   edi
  5286b3:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  5286b6:	b9 07 00 00 00       	mov    ecx,0x7
  5286bb:	be 74 62 b0 00       	mov    esi,0xb06274
  5286c0:	8d 7d dc             	lea    edi,[ebp-0x24]
  5286c3:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  5286c5:	8d 45 dc             	lea    eax,[ebp-0x24]
  5286c8:	50                   	push   eax
  5286c9:	6a 00                	push   0x0
  5286cb:	68 58 62 b0 00       	push   0xb06258
  5286d0:	68 4c 62 b0 00       	push   0xb0624c
  5286d5:	ff 15 14 f2 af 00    	call   DWORD PTR ds:0xaff214
  5286db:	89 45 d8             	mov    DWORD PTR [ebp-0x28],eax
  5286de:	8b 45 d8             	mov    eax,DWORD PTR [ebp-0x28]
  5286e1:	50                   	push   eax
  5286e2:	8b 0d d4 f0 40 02    	mov    ecx,DWORD PTR ds:0x240f0d4
  5286e8:	e8 c3 09 fe ff       	call   0x5090b0
  5286ed:	8d 45 dc             	lea    eax,[ebp-0x24]
  5286f0:	50                   	push   eax
  5286f1:	6a 05                	push   0x5
  5286f3:	68 30 62 b0 00       	push   0xb06230
  5286f8:	68 4c 62 b0 00       	push   0xb0624c
  5286fd:	ff 15 14 f2 af 00    	call   DWORD PTR ds:0xaff214
  528703:	89 45 d8             	mov    DWORD PTR [ebp-0x28],eax
  528706:	8a 45 d8             	mov    al,BYTE PTR [ebp-0x28]
  528709:	50                   	push   eax
  52870a:	8b 0d d4 f0 40 02    	mov    ecx,DWORD PTR ds:0x240f0d4
  528710:	e8 eb 09 fe ff       	call   0x509100
  528715:	8d 45 dc             	lea    eax,[ebp-0x24]
  528718:	50                   	push   eax
  528719:	6a 01                	push   0x1
  52871b:	68 28 62 b0 00       	push   0xb06228
  528720:	68 20 62 b0 00       	push   0xb06220
  528725:	ff 15 14 f2 af 00    	call   DWORD PTR ds:0xaff214
  52872b:	89 45 d8             	mov    DWORD PTR [ebp-0x28],eax
  52872e:	83 7d d8 05          	cmp    DWORD PTR [ebp-0x28],0x5
  528732:	7c 07                	jl     0x52873b
  528734:	c7 45 d8 01 00 00 00 	mov    DWORD PTR [ebp-0x28],0x1
  52873b:	8a 45 d8             	mov    al,BYTE PTR [ebp-0x28]
  52873e:	50                   	push   eax
  52873f:	8b 0d e8 f0 40 02    	mov    ecx,DWORD PTR ds:0x240f0e8
  528745:	e8 66 1f 20 00       	call   0x72a6b0


rf_online.bin:     file format pei-i386


Disassembly of section .text:

00732210 <.text+0x331210>:
  732210:	55                   	push   ebp
  732211:	8b ec                	mov    ebp,esp
  732213:	81 ec f8 00 00 00    	sub    esp,0xf8
  732219:	a1 dc 2e c0 00       	mov    eax,ds:0xc02edc
  73221e:	33 c5                	xor    eax,ebp
  732220:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  732223:	53                   	push   ebx
  732224:	56                   	push   esi
  732225:	57                   	push   edi
  732226:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  732229:	b9 07 00 00 00       	mov    ecx,0x7
  73222e:	be e0 0e b2 00       	mov    esi,0xb20ee0
  732233:	8d 7d d8             	lea    edi,[ebp-0x28]
  732236:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  732238:	a4                   	movs   BYTE PTR es:[edi],BYTE PTR ds:[esi]
  732239:	c6 85 58 ff ff ff 00 	mov    BYTE PTR [ebp-0xa8],0x0
  732240:	6a 7f                	push   0x7f
  732242:	6a 00                	push   0x0
  732244:	8d 85 59 ff ff ff    	lea    eax,[ebp-0xa7]
  73224a:	50                   	push   eax
  73224b:	e8 a0 f1 07 00       	call   0x7b13f0
  732250:	83 c4 0c             	add    esp,0xc
  732253:	8d 45 d8             	lea    eax,[ebp-0x28]
  732256:	50                   	push   eax
  732257:	6a 5a                	push   0x5a
  732259:	68 d4 0e b2 00       	push   0xb20ed4
  73225e:	68 cc 0e b2 00       	push   0xb20ecc
  732263:	ff 15 14 f2 af 00    	call   DWORD PTR ds:0xaff214
  732269:	89 85 54 ff ff ff    	mov    DWORD PTR [ebp-0xac],eax
  73226f:	8b 85 54 ff ff ff    	mov    eax,DWORD PTR [ebp-0xac]
  732275:	69 c0 e8 03 00 00    	imul   eax,eax,0x3e8
  73227b:	89 85 54 ff ff ff    	mov    DWORD PTR [ebp-0xac],eax


rf_online.bin:     file format pei-i386


Disassembly of section .text:

008219fd <.text+0x4209fd>:
  8219fd:	8b 1d fc f1 af 00    	mov    ebx,DWORD PTR ds:0xaff1fc
  821a03:	83 c4 10             	add    esp,0x10
  821a06:	68 14 d6 b3 00       	push   0xb3d614
  821a0b:	68 80 00 00 00       	push   0x80
  821a10:	68 60 48 51 02       	push   0x2514860
  821a15:	68 0c d6 b3 00       	push   0xb3d60c
  821a1a:	a3 58 48 51 02       	mov    ds:0x2514858,eax
  821a1f:	b8 00 00 80 3f       	mov    eax,0x3f800000
  821a24:	68 04 d6 b3 00       	push   0xb3d604
  821a29:	68 7c 84 b3 00       	push   0xb3847c
  821a2e:	c7 05 4c 51 51 02 ff 	mov    DWORD PTR ds:0x251514c,0xffffffff
  821a35:	ff ff ff
  821a38:	a3 50 51 51 02       	mov    ds:0x2515150,eax
  821a3d:	a3 54 51 51 02       	mov    ds:0x2515154,eax
  821a42:	a3 58 51 51 02       	mov    ds:0x2515158,eax
  821a47:	a3 5c 51 51 02       	mov    ds:0x251515c,eax
  821a4c:	a3 60 51 51 02       	mov    ds:0x2515160,eax
  821a51:	a3 64 51 51 02       	mov    ds:0x2515164,eax
  821a56:	a3 68 51 51 02       	mov    ds:0x2515168,eax
  821a5b:	a3 6c 51 51 02       	mov    ds:0x251516c,eax
  821a60:	a3 70 51 51 02       	mov    ds:0x2515170,eax
  821a65:	a3 74 51 51 02       	mov    ds:0x2515174,eax
  821a6a:	a3 78 51 51 02       	mov    ds:0x2515178,eax
  821a6f:	a3 7c 51 51 02       	mov    ds:0x251517c,eax
  821a74:	a3 80 51 51 02       	mov    ds:0x2515180,eax
  821a79:	a3 84 51 51 02       	mov    ds:0x2515184,eax
  821a7e:	a3 88 51 51 02       	mov    ds:0x2515188,eax
  821a83:	a3 8c 51 51 02       	mov    ds:0x251518c,eax
  821a88:	ff d3                	call   ebx
  821a8a:	68 14 d6 b3 00       	push   0xb3d614
  821a8f:	68 80 00 00 00       	push   0x80
  821a94:	68 e0 48 51 02       	push   0x25148e0
  821a99:	68 f8 d5 b3 00       	push   0xb3d5f8
  821a9e:	68 ec d5 b3 00       	push   0xb3d5ec
  821aa3:	68 7c 84 b3 00       	push   0xb3847c
  821aa8:	ff d3                	call   ebx
  821aaa:	68 14 d6 b3 00       	push   0xb3d614
  821aaf:	68 80 00 00 00       	push   0x80
  821ab4:	68 60 49 51 02       	push   0x2514960
  821ab9:	68 dc d5 b3 00       	push   0xb3d5dc
  821abe:	68 d0 d5 b3 00       	push   0xb3d5d0
  821ac3:	68 7c 84 b3 00       	push   0xb3847c
  821ac8:	ff d3                	call   ebx
  821aca:	68 14 d6 b3 00       	push   0xb3d614
  821acf:	68 80 00 00 00       	push   0x80
  821ad4:	68 e0 49 51 02       	push   0x25149e0
  821ad9:	68 c4 d5 b3 00       	push   0xb3d5c4
  821ade:	68 b8 d5 b3 00       	push   0xb3d5b8
  821ae3:	68 7c 84 b3 00       	push   0xb3847c
  821ae8:	ff d3                	call   ebx
  821aea:	68 14 d6 b3 00       	push   0xb3d614
  821aef:	68 80 00 00 00       	push   0x80
  821af4:	68 60 4a 51 02       	push   0x2514a60
  821af9:	68 a8 d5 b3 00       	push   0xb3d5a8
  821afe:	68 98 d5 b3 00       	push   0xb3d598
  821b03:	68 7c 84 b3 00       	push   0xb3847c
  821b08:	ff d3                	call   ebx
  821b0a:	68 14 d6 b3 00       	push   0xb3d614
  821b0f:	68 80 00 00 00       	push   0x80
  821b14:	68 e0 4a 51 02       	push   0x2514ae0
  821b19:	68 90 d5 b3 00       	push   0xb3d590
  821b1e:	68 84 d5 b3 00       	push   0xb3d584
  821b23:	68 7c 84 b3 00       	push   0xb3847c
  821b28:	ff d3                	call   ebx
