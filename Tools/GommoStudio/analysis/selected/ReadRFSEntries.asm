gommostudio.exe:     file format pei-x86-64


Disassembly of section .text:

00000001408ea940 <.text+0x8e9940>:
   1408ea940:	4c 8d 64 24 a8       	lea    r12,[rsp-0x58]
   1408ea945:	4d 3b 66 10          	cmp    r12,QWORD PTR [r14+0x10]
   1408ea949:	0f 86 6f 04 00 00    	jbe    0x1408eadbe
   1408ea94f:	55                   	push   rbp
   1408ea950:	48 89 e5             	mov    rbp,rsp
   1408ea953:	48 81 ec d0 00 00 00 	sub    rsp,0xd0
   1408ea95a:	48 89 84 24 e0 00 00 	mov    QWORD PTR [rsp+0xe0],rax
   1408ea961:	00
   1408ea962:	48 83 fb 04          	cmp    rbx,0x4
   1408ea966:	0f 8c f7 00 00 00    	jl     0x1408eaa63
   1408ea96c:	48 89 9c 24 e8 00 00 	mov    QWORD PTR [rsp+0xe8],rbx
   1408ea973:	00
   1408ea974:	8b 10                	mov    edx,DWORD PTR [rax]
   1408ea976:	48 89 d6             	mov    rsi,rdx
   1408ea979:	48 c1 e2 06          	shl    rdx,0x6
   1408ea97d:	48 83 c2 04          	add    rdx,0x4
   1408ea981:	90                   	nop
   1408ea982:	48 39 d3             	cmp    rbx,rdx
   1408ea985:	7c 50                	jl     0x1408ea9d7
   1408ea987:	48 89 74 24 48       	mov    QWORD PTR [rsp+0x48],rsi
   1408ea98c:	48 89 8c 24 f0 00 00 	mov    QWORD PTR [rsp+0xf0],rcx
   1408ea993:	00
   1408ea994:	48 89 84 24 e0 00 00 	mov    QWORD PTR [rsp+0xe0],rax
   1408ea99b:	00
   1408ea99c:	48 8d 05 fd 42 e0 01 	lea    rax,[rip+0x1e042fd]        # 0x1426eeca0
   1408ea9a3:	48 89 f3             	mov    rbx,rsi
   1408ea9a6:	48 89 d9             	mov    rcx,rbx
   1408ea9a9:	e8 32 b9 78 ff       	call   0x1400762e0
   1408ea9ae:	48 89 44 24 58       	mov    QWORD PTR [rsp+0x58],rax
   1408ea9b3:	48 8b 4c 24 48       	mov    rcx,QWORD PTR [rsp+0x48]
   1408ea9b8:	48 8b 94 24 e8 00 00 	mov    rdx,QWORD PTR [rsp+0xe8]
   1408ea9bf:	00
   1408ea9c0:	48 8b b4 24 f0 00 00 	mov    rsi,QWORD PTR [rsp+0xf0]
   1408ea9c7:	00
   1408ea9c8:	48 8b bc 24 e0 00 00 	mov    rdi,QWORD PTR [rsp+0xe0]
   1408ea9cf:	00
   1408ea9d0:	31 db                	xor    ebx,ebx
   1408ea9d2:	e9 13 01 00 00       	jmp    0x1408eaaea
   1408ea9d7:	44 0f 11 bc 24 a0 00 	movups XMMWORD PTR [rsp+0xa0],xmm15
   1408ea9de:	00 00
   1408ea9e0:	44 0f 11 bc 24 b0 00 	movups XMMWORD PTR [rsp+0xb0],xmm15
   1408ea9e7:	00 00
   1408ea9e9:	48 89 f0             	mov    rax,rsi
   1408ea9ec:	e8 6f 70 78 ff       	call   0x140071a60
   1408ea9f1:	48 8d 0d 68 17 b8 01 	lea    rcx,[rip+0x1b81768]        # 0x14246c160
   1408ea9f8:	48 89 8c 24 a0 00 00 	mov    QWORD PTR [rsp+0xa0],rcx
   1408ea9ff:	00
   1408eaa00:	48 89 84 24 a8 00 00 	mov    QWORD PTR [rsp+0xa8],rax
   1408eaa07:	00
   1408eaa08:	48 8b 84 24 e8 00 00 	mov    rax,QWORD PTR [rsp+0xe8]
   1408eaa0f:	00
   1408eaa10:	e8 4b 70 78 ff       	call   0x140071a60
   1408eaa15:	48 8d 0d 44 17 b8 01 	lea    rcx,[rip+0x1b81744]        # 0x14246c160
   1408eaa1c:	48 89 8c 24 b0 00 00 	mov    QWORD PTR [rsp+0xb0],rcx
   1408eaa23:	00
   1408eaa24:	48 89 84 24 b8 00 00 	mov    QWORD PTR [rsp+0xb8],rax
   1408eaa2b:	00
   1408eaa2c:	48 8d 05 ed 5b 0e 02 	lea    rax,[rip+0x20e5bed]        # 0x1429d0620
   1408eaa33:	bb 2d 00 00 00       	mov    ebx,0x2d
   1408eaa38:	48 8d 8c 24 a0 00 00 	lea    rcx,[rsp+0xa0]
   1408eaa3f:	00
   1408eaa40:	bf 02 00 00 00       	mov    edi,0x2
   1408eaa45:	48 89 fe             	mov    rsi,rdi
   1408eaa48:	e8 13 c6 82 ff       	call   0x140117060
   1408eaa4d:	31 c9                	xor    ecx,ecx
   1408eaa4f:	48 89 c7             	mov    rdi,rax
   1408eaa52:	48 89 de             	mov    rsi,rbx
   1408eaa55:	31 c0                	xor    eax,eax
   1408eaa57:	48 89 cb             	mov    rbx,rcx
   1408eaa5a:	48 81 c4 d0 00 00 00 	add    rsp,0xd0
   1408eaa61:	5d                   	pop    rbp
   1408eaa62:	c3                   	ret
   1408eaa63:	44 0f 11 bc 24 c0 00 	movups XMMWORD PTR [rsp+0xc0],xmm15
   1408eaa6a:	00 00
   1408eaa6c:	48 89 d8             	mov    rax,rbx
   1408eaa6f:	e8 ec 6f 78 ff       	call   0x140071a60
   1408eaa74:	48 8d 0d e5 16 b8 01 	lea    rcx,[rip+0x1b816e5]        # 0x14246c160
   1408eaa7b:	48 89 8c 24 c0 00 00 	mov    QWORD PTR [rsp+0xc0],rcx
   1408eaa82:	00
   1408eaa83:	48 89 84 24 c8 00 00 	mov    QWORD PTR [rsp+0xc8],rax
   1408eaa8a:	00
   1408eaa8b:	48 8d 05 fc 87 05 02 	lea    rax,[rip+0x20587fc]        # 0x14294328e
   1408eaa92:	bb 0d 00 00 00       	mov    ebx,0xd
   1408eaa97:	48 8d 8c 24 c0 00 00 	lea    rcx,[rsp+0xc0]
   1408eaa9e:	00
   1408eaa9f:	bf 01 00 00 00       	mov    edi,0x1
   1408eaaa4:	48 89 fe             	mov    rsi,rdi
   1408eaaa7:	e8 b4 c5 82 ff       	call   0x140117060
   1408eaaac:	31 c9                	xor    ecx,ecx
   1408eaaae:	48 89 c7             	mov    rdi,rax
   1408eaab1:	48 89 de             	mov    rsi,rbx
   1408eaab4:	31 c0                	xor    eax,eax
   1408eaab6:	48 89 cb             	mov    rbx,rcx
   1408eaab9:	48 81 c4 d0 00 00 00 	add    rsp,0xd0
   1408eaac0:	5d                   	pop    rbp
   1408eaac1:	c3                   	ret
   1408eaac2:	4c 89 4c 16 10       	mov    QWORD PTR [rsi+rdx*1+0x10],r9
   1408eaac7:	44 89 44 16 60       	mov    DWORD PTR [rsi+rdx*1+0x60],r8d
   1408eaacc:	48 8b 5c 24 40       	mov    rbx,QWORD PTR [rsp+0x40]
   1408eaad1:	48 ff c3             	inc    rbx
   1408eaad4:	48 89 f0             	mov    rax,rsi
   1408eaad7:	48 8b 4c 24 48       	mov    rcx,QWORD PTR [rsp+0x48]
   1408eaadc:	48 8b 94 24 e8 00 00 	mov    rdx,QWORD PTR [rsp+0xe8]
   1408eaae3:	00
   1408eaae4:	4c 89 d6             	mov    rsi,r10
   1408eaae7:	4c 89 df             	mov    rdi,r11
   1408eaaea:	48 39 cb             	cmp    rbx,rcx
   1408eaaed:	0f 8d 6a 02 00 00    	jge    0x1408ead5d
   1408eaaf3:	49 89 d8             	mov    r8,rbx
   1408eaaf6:	48 c1 e3 06          	shl    rbx,0x6
   1408eaafa:	4c 8d 4b 04          	lea    r9,[rbx+0x4]
   1408eaafe:	66 90                	xchg   ax,ax
   1408eab00:	4c 39 ca             	cmp    rdx,r9
   1408eab03:	0f 82 a9 02 00 00    	jb     0x1408eadb2
   1408eab09:	48 29 de             	sub    rsi,rbx
   1408eab0c:	49 89 d3             	mov    r11,rdx
   1408eab0f:	48 29 da             	sub    rdx,rbx
   1408eab12:	4c 8d 62 fc          	lea    r12,[rdx-0x4]
   1408eab16:	4c 8d 6e fc          	lea    r13,[rsi-0x4]
   1408eab1a:	4d 89 ef             	mov    r15,r13
   1408eab1d:	49 f7 dd             	neg    r13
   1408eab20:	49 c1 fd 3f          	sar    r13,0x3f
   1408eab24:	4d 21 cd             	and    r13,r9
   1408eab27:	4a 8d 1c 2f          	lea    rbx,[rdi+r13*1]
   1408eab2b:	49 83 fc 38          	cmp    r12,0x38
   1408eab2f:	0f 82 70 02 00 00    	jb     0x1408eada5
   1408eab35:	4c 8d 4a c4          	lea    r9,[rdx-0x3c]
   1408eab39:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   1408eab40:	49 83 f9 03          	cmp    r9,0x3
   1408eab44:	0f 86 4d 02 00 00    	jbe    0x1408ead97
   1408eab4a:	4c 8d 4e c4          	lea    r9,[rsi-0x3c]
   1408eab4e:	49 f7 d9             	neg    r9
   1408eab51:	49 c1 f9 3f          	sar    r9,0x3f
   1408eab55:	41 83 e1 38          	and    r9d,0x38
   1408eab59:	45 8b 0c 19          	mov    r9d,DWORD PTR [r9+rbx*1]
   1408eab5d:	0f 1f 00             	nop    DWORD PTR [rax]
   1408eab60:	49 83 fc 3c          	cmp    r12,0x3c
   1408eab64:	0f 82 20 02 00 00    	jb     0x1408ead8a
   1408eab6a:	48 83 c2 c0          	add    rdx,0xffffffffffffffc0
   1408eab6e:	48 83 fa 03          	cmp    rdx,0x3
   1408eab72:	0f 86 05 02 00 00    	jbe    0x1408ead7d
   1408eab78:	44 89 4c 24 2c       	mov    DWORD PTR [rsp+0x2c],r9d
   1408eab7d:	48 8d 56 c0          	lea    rdx,[rsi-0x40]
   1408eab81:	48 f7 da             	neg    rdx
   1408eab84:	48 c1 fa 3f          	sar    rdx,0x3f
   1408eab88:	83 e2 3c             	and    edx,0x3c
   1408eab8b:	8b 14 1a             	mov    edx,DWORD PTR [rdx+rbx*1]
   1408eab8e:	89 54 24 28          	mov    DWORD PTR [rsp+0x28],edx
   1408eab92:	49 8d 34 11          	lea    rsi,[r9+rdx*1]
   1408eab96:	49 39 f3             	cmp    r11,rsi
   1408eab99:	0f 82 f5 00 00 00    	jb     0x1408eac94
   1408eab9f:	4c 89 44 24 40       	mov    QWORD PTR [rsp+0x40],r8
   1408eaba4:	49 6b f0 68          	imul   rsi,r8,0x68
   1408eaba8:	48 89 74 24 38       	mov    QWORD PTR [rsp+0x38],rsi
   1408eabad:	4c 8d 24 30          	lea    r12,[rax+rsi*1]
   1408eabb1:	4d 8d 64 24 28       	lea    r12,[r12+0x28]
   1408eabb6:	49 39 dc             	cmp    r12,rbx
   1408eabb9:	74 21                	je     0x1408eabdc
   1408eabbb:	4c 89 7c 24 30       	mov    QWORD PTR [rsp+0x30],r15
   1408eabc0:	48 89 5c 24 50       	mov    QWORD PTR [rsp+0x50],rbx
   1408eabc5:	4c 89 e0             	mov    rax,r12
   1408eabc8:	b9 38 00 00 00       	mov    ecx,0x38
   1408eabcd:	e8 6e 27 79 ff       	call   0x14007d340
   1408eabd2:	48 8b 5c 24 50       	mov    rbx,QWORD PTR [rsp+0x50]
   1408eabd7:	4c 8b 7c 24 30       	mov    r15,QWORD PTR [rsp+0x30]
   1408eabdc:	48 89 d8             	mov    rax,rbx
   1408eabdf:	bb 38 00 00 00       	mov    ebx,0x38
   1408eabe4:	4c 89 f9             	mov    rcx,r15
   1408eabe7:	e8 f4 4e cc ff       	call   0x1405afae0
   1408eabec:	48 8b 54 24 38       	mov    rdx,QWORD PTR [rsp+0x38]
   1408eabf1:	48 8b 74 24 58       	mov    rsi,QWORD PTR [rsp+0x58]
   1408eabf6:	48 89 5c 16 08       	mov    QWORD PTR [rsi+rdx*1+0x8],rbx
   1408eabfb:	8b 7c 24 28          	mov    edi,DWORD PTR [rsp+0x28]
   1408eabff:	44 8b 44 24 2c       	mov    r8d,DWORD PTR [rsp+0x2c]
   1408eac04:	41 8d 0c 38          	lea    ecx,[r8+rdi*1]
   1408eac08:	83 3d 51 c0 be 03 00 	cmp    DWORD PTR [rip+0x3bec051],0x0        # 0x1444d6c60
   1408eac0f:	74 10                	je     0x1408eac21
   1408eac11:	4c 8b 0c 16          	mov    r9,QWORD PTR [rsi+rdx*1]
   1408eac15:	e8 86 19 79 ff       	call   0x14007c5a0
   1408eac1a:	49 89 03             	mov    QWORD PTR [r11],rax
   1408eac1d:	4d 89 4b 08          	mov    QWORD PTR [r11+0x8],r9
   1408eac21:	48 89 04 16          	mov    QWORD PTR [rsi+rdx*1],rax
   1408eac25:	4c 8b 8c 24 f0 00 00 	mov    r9,QWORD PTR [rsp+0xf0]
   1408eac2c:	00
   1408eac2d:	49 39 c9             	cmp    r9,rcx
   1408eac30:	0f 82 3f 01 00 00    	jb     0x1408ead75
   1408eac36:	49 39 c8             	cmp    r8,rcx
   1408eac39:	0f 87 2e 01 00 00    	ja     0x1408ead6d
   1408eac3f:	4d 89 ca             	mov    r10,r9
   1408eac42:	4d 29 c1             	sub    r9,r8
   1408eac45:	4c 29 c1             	sub    rcx,r8
   1408eac48:	48 89 4c 16 18       	mov    QWORD PTR [rsi+rdx*1+0x18],rcx
   1408eac4d:	4c 89 4c 16 20       	mov    QWORD PTR [rsi+rdx*1+0x20],r9
   1408eac52:	49 f7 d9             	neg    r9
   1408eac55:	49 c1 f9 3f          	sar    r9,0x3f
   1408eac59:	4d 21 c1             	and    r9,r8
   1408eac5c:	4c 8b 9c 24 e0 00 00 	mov    r11,QWORD PTR [rsp+0xe0]
   1408eac63:	00
   1408eac64:	4d 01 d9             	add    r9,r11
   1408eac67:	83 3d f2 bf be 03 00 	cmp    DWORD PTR [rip+0x3bebff2],0x0        # 0x1444d6c60
   1408eac6e:	0f 84 4e fe ff ff    	je     0x1408eaac2
   1408eac74:	4c 8b 64 16 10       	mov    r12,QWORD PTR [rsi+rdx*1+0x10]
   1408eac79:	4c 89 d8             	mov    rax,r11
   1408eac7c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   1408eac80:	e8 1b 19 79 ff       	call   0x14007c5a0
   1408eac85:	4d 89 0b             	mov    QWORD PTR [r11],r9
   1408eac88:	4d 89 63 08          	mov    QWORD PTR [r11+0x8],r12
   1408eac8c:	49 89 c3             	mov    r11,rax
   1408eac8f:	e9 2e fe ff ff       	jmp    0x1408eaac2
   1408eac94:	44 0f 11 7c 24 60    	movups XMMWORD PTR [rsp+0x60],xmm15
   1408eac9a:	44 0f 11 7c 24 70    	movups XMMWORD PTR [rsp+0x70],xmm15
   1408eaca0:	44 0f 11 bc 24 80 00 	movups XMMWORD PTR [rsp+0x80],xmm15
   1408eaca7:	00 00
   1408eaca9:	44 0f 11 bc 24 90 00 	movups XMMWORD PTR [rsp+0x90],xmm15
   1408eacb0:	00 00
   1408eacb2:	4c 89 c0             	mov    rax,r8
   1408eacb5:	e8 a6 6d 78 ff       	call   0x140071a60
   1408eacba:	48 8d 0d 9f 14 b8 01 	lea    rcx,[rip+0x1b8149f]        # 0x14246c160
   1408eacc1:	48 89 4c 24 60       	mov    QWORD PTR [rsp+0x60],rcx
   1408eacc6:	48 89 44 24 68       	mov    QWORD PTR [rsp+0x68],rax
   1408eaccb:	8b 44 24 2c          	mov    eax,DWORD PTR [rsp+0x2c]
   1408eaccf:	e8 4c 85 72 ff       	call   0x140013220
   1408eacd4:	48 8d 0d c5 13 b8 01 	lea    rcx,[rip+0x1b813c5]        # 0x14246c0a0
   1408eacdb:	48 89 4c 24 70       	mov    QWORD PTR [rsp+0x70],rcx
   1408eace0:	48 89 44 24 78       	mov    QWORD PTR [rsp+0x78],rax
   1408eace5:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
   1408eace9:	e8 32 85 72 ff       	call   0x140013220
   1408eacee:	48 8d 0d ab 13 b8 01 	lea    rcx,[rip+0x1b813ab]        # 0x14246c0a0
   1408eacf5:	48 89 8c 24 80 00 00 	mov    QWORD PTR [rsp+0x80],rcx
   1408eacfc:	00
   1408eacfd:	48 89 84 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rax
   1408ead04:	00
   1408ead05:	48 8b 84 24 e8 00 00 	mov    rax,QWORD PTR [rsp+0xe8]
   1408ead0c:	00
   1408ead0d:	e8 4e 6d 78 ff       	call   0x140071a60
   1408ead12:	48 8d 0d 47 14 b8 01 	lea    rcx,[rip+0x1b81447]        # 0x14246c160
   1408ead19:	48 89 8c 24 90 00 00 	mov    QWORD PTR [rsp+0x90],rcx
   1408ead20:	00
   1408ead21:	48 89 84 24 98 00 00 	mov    QWORD PTR [rsp+0x98],rax
   1408ead28:	00
   1408ead29:	48 8d 05 16 1b 0d 02 	lea    rax,[rip+0x20d1b16]        # 0x1429bc846
   1408ead30:	bb 27 00 00 00       	mov    ebx,0x27
   1408ead35:	48 8d 4c 24 60       	lea    rcx,[rsp+0x60]
   1408ead3a:	bf 04 00 00 00       	mov    edi,0x4
   1408ead3f:	48 89 fe             	mov    rsi,rdi
   1408ead42:	e8 19 c3 82 ff       	call   0x140117060
   1408ead47:	31 c9                	xor    ecx,ecx
   1408ead49:	48 89 c7             	mov    rdi,rax
   1408ead4c:	48 89 de             	mov    rsi,rbx
   1408ead4f:	31 c0                	xor    eax,eax
   1408ead51:	48 89 cb             	mov    rbx,rcx
   1408ead54:	48 81 c4 d0 00 00 00 	add    rsp,0xd0
   1408ead5b:	5d                   	pop    rbp
   1408ead5c:	c3                   	ret
   1408ead5d:	48 89 cb             	mov    rbx,rcx
   1408ead60:	31 ff                	xor    edi,edi
   1408ead62:	31 f6                	xor    esi,esi
   1408ead64:	48 81 c4 d0 00 00 00 	add    rsp,0xd0
   1408ead6b:	5d                   	pop    rbp
   1408ead6c:	c3                   	ret
   1408ead6d:	44 89 c0             	mov    eax,r8d
   1408ead70:	e8 8b 1c 79 ff       	call   0x14007ca00
   1408ead75:	4c 89 ca             	mov    rdx,r9
   1408ead78:	e8 43 1c 79 ff       	call   0x14007c9c0
   1408ead7d:	b8 03 00 00 00       	mov    eax,0x3
   1408ead82:	48 89 d1             	mov    rcx,rdx
   1408ead85:	e8 b6 1b 79 ff       	call   0x14007c940
   1408ead8a:	b8 3c 00 00 00       	mov    eax,0x3c
   1408ead8f:	4c 89 e1             	mov    rcx,r12
   1408ead92:	e8 69 1c 79 ff       	call   0x14007ca00
   1408ead97:	b8 03 00 00 00       	mov    eax,0x3
   1408ead9c:	4c 89 c9             	mov    rcx,r9
   1408ead9f:	90                   	nop
   1408eada0:	e8 9b 1b 79 ff       	call   0x14007c940
   1408eada5:	b8 38 00 00 00       	mov    eax,0x38
   1408eadaa:	4c 89 e1             	mov    rcx,r12
   1408eadad:	e8 4e 1c 79 ff       	call   0x14007ca00
   1408eadb2:	4c 89 c8             	mov    rax,r9
   1408eadb5:	48 89 d1             	mov    rcx,rdx
   1408eadb8:	e8 43 1c 79 ff       	call   0x14007ca00
   1408eadbd:	90                   	nop
   1408eadbe:	48 89 44 24 08       	mov    QWORD PTR [rsp+0x8],rax
   1408eadc3:	48 89 5c 24 10       	mov    QWORD PTR [rsp+0x10],rbx
   1408eadc8:	48 89 4c 24 18       	mov    QWORD PTR [rsp+0x18],rcx
   1408eadcd:	e8 ae f8 78 ff       	call   0x14007a680
   1408eadd2:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
   1408eadd7:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
   1408eaddc:	48 8b 4c 24 18       	mov    rcx,QWORD PTR [rsp+0x18]
   1408eade1:	e9 5a fb ff ff       	jmp    0x1408ea940
   1408eade6:	cc                   	int3
   1408eade7:	cc                   	int3
   1408eade8:	cc                   	int3
   1408eade9:	cc                   	int3
   1408eadea:	cc                   	int3
   1408eadeb:	cc                   	int3
   1408eadec:	cc                   	int3
   1408eaded:	cc                   	int3
   1408eadee:	cc                   	int3
   1408eadef:	cc                   	int3
   1408eadf0:	cc                   	int3
   1408eadf1:	cc                   	int3
   1408eadf2:	cc                   	int3
   1408eadf3:	cc                   	int3
   1408eadf4:	cc                   	int3
   1408eadf5:	cc                   	int3
   1408eadf6:	cc                   	int3
   1408eadf7:	cc                   	int3
   1408eadf8:	cc                   	int3
   1408eadf9:	cc                   	int3
   1408eadfa:	cc                   	int3
   1408eadfb:	cc                   	int3
   1408eadfc:	cc                   	int3
   1408eadfd:	cc                   	int3
   1408eadfe:	cc                   	int3
   1408eadff:	cc                   	int3
