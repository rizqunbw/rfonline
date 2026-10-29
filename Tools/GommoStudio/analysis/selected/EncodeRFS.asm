gommostudio.exe:     file format pei-x86-64


Disassembly of section .text:

00000001408eae00 <.text+0x8e9e00>:
   1408eae00:	4c 8d a4 24 d8 fe ff 	lea    r12,[rsp-0x128]
   1408eae07:	ff
   1408eae08:	4d 3b 66 10          	cmp    r12,QWORD PTR [r14+0x10]
   1408eae0c:	0f 86 81 05 00 00    	jbe    0x1408eb393
   1408eae12:	55                   	push   rbp
   1408eae13:	48 89 e5             	mov    rbp,rsp
   1408eae16:	48 81 ec a0 01 00 00 	sub    rsp,0x1a0
   1408eae1d:	48 89 84 24 b0 01 00 	mov    QWORD PTR [rsp+0x1b0],rax
   1408eae24:	00
   1408eae25:	48 89 da             	mov    rdx,rbx
   1408eae28:	48 c1 e2 06          	shl    rdx,0x6
   1408eae2c:	4c 8d 42 04          	lea    r8,[rdx+0x4]
   1408eae30:	49 89 c1             	mov    r9,rax
   1408eae33:	4c 89 c1             	mov    rcx,r8
   1408eae36:	31 f6                	xor    esi,esi
   1408eae38:	eb 4c                	jmp    0x1408eae86
   1408eae3a:	4c 8b 10             	mov    r10,QWORD PTR [rax]
   1408eae3d:	4c 89 94 24 38 01 00 	mov    QWORD PTR [rsp+0x138],r10
   1408eae44:	00
   1408eae45:	4c 8d 50 08          	lea    r10,[rax+0x8]
   1408eae49:	48 8d bc 24 40 01 00 	lea    rdi,[rsp+0x140]
   1408eae50:	00
   1408eae51:	49 89 f3             	mov    r11,rsi
   1408eae54:	4c 89 d6             	mov    rsi,r10
   1408eae57:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
   1408eae5e:	00 00
   1408eae60:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
   1408eae65:	48 8d 6c 24 f0       	lea    rbp,[rsp-0x10]
   1408eae6a:	e8 5d 21 79 ff       	call   0x14007cfcc
   1408eae6f:	48 8b 6d 00          	mov    rbp,QWORD PTR [rbp+0x0]
   1408eae73:	4c 8b 94 24 50 01 00 	mov    r10,QWORD PTR [rsp+0x150]
   1408eae7a:	00
   1408eae7b:	48 83 c0 68          	add    rax,0x68
   1408eae7f:	4d 01 d0             	add    r8,r10
   1408eae82:	49 8d 73 01          	lea    rsi,[r11+0x1]
   1408eae86:	48 39 f3             	cmp    rbx,rsi
   1408eae89:	7f af                	jg     0x1408eae3a
   1408eae8b:	be ff ff ff ff       	mov    esi,0xffffffff
   1408eae90:	49 39 f0             	cmp    r8,rsi
   1408eae93:	77 7f                	ja     0x1408eaf14
   1408eae95:	48 89 94 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rdx
   1408eae9c:	00
   1408eae9d:	48 89 8c 24 80 00 00 	mov    QWORD PTR [rsp+0x80],rcx
   1408eaea4:	00
   1408eaea5:	48 89 9c 24 b8 01 00 	mov    QWORD PTR [rsp+0x1b8],rbx
   1408eaeac:	00
   1408eaead:	4c 89 8c 24 20 01 00 	mov    QWORD PTR [rsp+0x120],r9
   1408eaeb4:	00
   1408eaeb5:	4c 89 44 24 40       	mov    QWORD PTR [rsp+0x40],r8
   1408eaeba:	48 8d 05 df 10 b8 01 	lea    rax,[rip+0x1b810df]        # 0x14246bfa0
   1408eaec1:	48 89 cb             	mov    rbx,rcx
   1408eaec4:	4c 89 c1             	mov    rcx,r8
   1408eaec7:	e8 14 b4 78 ff       	call   0x1400762e0
   1408eaecc:	90                   	nop
   1408eaecd:	48 8b 8c 24 80 00 00 	mov    rcx,QWORD PTR [rsp+0x80]
   1408eaed4:	00
   1408eaed5:	48 83 f9 03          	cmp    rcx,0x3
   1408eaed9:	0f 86 a9 04 00 00    	jbe    0x1408eb388
   1408eaedf:	48 89 84 24 18 01 00 	mov    QWORD PTR [rsp+0x118],rax
   1408eaee6:	00
   1408eaee7:	4c 8b 9c 24 b8 01 00 	mov    r11,QWORD PTR [rsp+0x1b8]
   1408eaeee:	00
   1408eaeef:	44 89 18             	mov    DWORD PTR [rax],r11d
   1408eaef2:	4c 8b a4 24 20 01 00 	mov    r12,QWORD PTR [rsp+0x120]
   1408eaef9:	00
   1408eaefa:	4d 89 e5             	mov    r13,r12
   1408eaefd:	4c 8b bc 24 88 00 00 	mov    r15,QWORD PTR [rsp+0x88]
   1408eaf04:	00
   1408eaf05:	48 8b 54 24 40       	mov    rdx,QWORD PTR [rsp+0x40]
   1408eaf0a:	48 89 cb             	mov    rbx,rcx
   1408eaf0d:	31 f6                	xor    esi,esi
   1408eaf0f:	e9 cc 00 00 00       	jmp    0x1408eafe0
   1408eaf14:	44 0f 11 bc 24 28 01 	movups XMMWORD PTR [rsp+0x128],xmm15
   1408eaf1b:	00 00
   1408eaf1d:	4c 89 c0             	mov    rax,r8
   1408eaf20:	e8 3b 6b 78 ff       	call   0x140071a60
   1408eaf25:	48 8d 0d 34 12 b8 01 	lea    rcx,[rip+0x1b81234]        # 0x14246c160
   1408eaf2c:	48 89 8c 24 28 01 00 	mov    QWORD PTR [rsp+0x128],rcx
   1408eaf33:	00
   1408eaf34:	48 89 84 24 30 01 00 	mov    QWORD PTR [rsp+0x130],rax
   1408eaf3b:	00
   1408eaf3c:	48 8d 05 26 8c 0d 02 	lea    rax,[rip+0x20d8c26]        # 0x1429c3b69
   1408eaf43:	bb 29 00 00 00       	mov    ebx,0x29
   1408eaf48:	48 8d 8c 24 28 01 00 	lea    rcx,[rsp+0x128]
   1408eaf4f:	00
   1408eaf50:	bf 01 00 00 00       	mov    edi,0x1
   1408eaf55:	48 89 fe             	mov    rsi,rdi
   1408eaf58:	e8 03 c1 82 ff       	call   0x140117060
   1408eaf5d:	31 c9                	xor    ecx,ecx
   1408eaf5f:	48 89 c7             	mov    rdi,rax
   1408eaf62:	48 89 de             	mov    rsi,rbx
   1408eaf65:	31 c0                	xor    eax,eax
   1408eaf67:	48 89 cb             	mov    rbx,rcx
   1408eaf6a:	48 81 c4 a0 01 00 00 	add    rsp,0x1a0
   1408eaf71:	5d                   	pop    rbp
   1408eaf72:	c3                   	ret
   1408eaf73:	49 8d 43 c0          	lea    rax,[r11-0x40]
   1408eaf77:	48 f7 d8             	neg    rax
   1408eaf7a:	48 c1 f8 3f          	sar    rax,0x3f
   1408eaf7e:	83 e0 3c             	and    eax,0x3c
   1408eaf81:	48 8b 8c 24 b8 00 00 	mov    rcx,QWORD PTR [rsp+0xb8]
   1408eaf88:	00
   1408eaf89:	41 89 0c 07          	mov    DWORD PTR [r15+rax*1],ecx
   1408eaf8d:	4c 8b a4 24 10 01 00 	mov    r12,QWORD PTR [rsp+0x110]
   1408eaf94:	00
   1408eaf95:	49 83 c4 68          	add    r12,0x68
   1408eaf99:	4c 03 ac 24 b8 00 00 	add    r13,QWORD PTR [rsp+0xb8]
   1408eafa0:	00
   1408eafa1:	48 8b 74 24 78       	mov    rsi,QWORD PTR [rsp+0x78]
   1408eafa6:	48 ff c6             	inc    rsi
   1408eafa9:	48 8b 84 24 18 01 00 	mov    rax,QWORD PTR [rsp+0x118]
   1408eafb0:	00
   1408eafb1:	48 8b 54 24 40       	mov    rdx,QWORD PTR [rsp+0x40]
   1408eafb6:	48 8b 9c 24 80 00 00 	mov    rbx,QWORD PTR [rsp+0x80]
   1408eafbd:	00
   1408eafbe:	4c 8b 9c 24 b8 01 00 	mov    r11,QWORD PTR [rsp+0x1b8]
   1408eafc5:	00
   1408eafc6:	4c 8b bc 24 88 00 00 	mov    r15,QWORD PTR [rsp+0x88]
   1408eafcd:	00
   1408eafce:	4c 89 e9             	mov    rcx,r13
   1408eafd1:	4c 8b ac 24 20 01 00 	mov    r13,QWORD PTR [rsp+0x120]
   1408eafd8:	00
   1408eafd9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   1408eafe0:	49 39 f3             	cmp    r11,rsi
   1408eafe3:	0f 8e 3f 02 00 00    	jle    0x1408eb228
   1408eafe9:	49 8b 3c 24          	mov    rdi,QWORD PTR [r12]
   1408eafed:	4d 8d 44 24 08       	lea    r8,[r12+0x8]
   1408eaff2:	48 89 bc 24 38 01 00 	mov    QWORD PTR [rsp+0x138],rdi
   1408eaff9:	00
   1408eaffa:	48 8d bc 24 40 01 00 	lea    rdi,[rsp+0x140]
   1408eb001:	00
   1408eb002:	49 89 f1             	mov    r9,rsi
   1408eb005:	4c 89 c6             	mov    rsi,r8
   1408eb008:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
   1408eb00d:	48 8d 6c 24 f0       	lea    rbp,[rsp-0x10]
   1408eb012:	e8 b5 1f 79 ff       	call   0x14007cfcc
   1408eb017:	48 8b 6d 00          	mov    rbp,QWORD PTR [rbp+0x0]
   1408eb01b:	48 8b b4 24 38 01 00 	mov    rsi,QWORD PTR [rsp+0x138]
   1408eb022:	00
   1408eb023:	48 89 b4 24 a0 00 00 	mov    QWORD PTR [rsp+0xa0],rsi
   1408eb02a:	00
   1408eb02b:	48 8d bc 24 a8 00 00 	lea    rdi,[rsp+0xa8]
   1408eb032:	00
   1408eb033:	48 8d b4 24 40 01 00 	lea    rsi,[rsp+0x140]
   1408eb03a:	00
   1408eb03b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
   1408eb040:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
   1408eb045:	48 8d 6c 24 f0       	lea    rbp,[rsp-0x10]
   1408eb04a:	e8 7d 1f 79 ff       	call   0x14007cfcc
   1408eb04f:	48 8b 6d 00          	mov    rbp,QWORD PTR [rbp+0x0]
   1408eb053:	4c 89 ce             	mov    rsi,r9
   1408eb056:	49 c1 e1 06          	shl    r9,0x6
   1408eb05a:	49 8d 79 04          	lea    rdi,[r9+0x4]
   1408eb05e:	66 90                	xchg   ax,ax
   1408eb060:	48 39 df             	cmp    rdi,rbx
   1408eb063:	0f 87 14 03 00 00    	ja     0x1408eb37d
   1408eb069:	48 89 74 24 78       	mov    QWORD PTR [rsp+0x78],rsi
   1408eb06e:	4c 89 a4 24 10 01 00 	mov    QWORD PTR [rsp+0x110],r12
   1408eb075:	00
   1408eb076:	48 89 4c 24 60       	mov    QWORD PTR [rsp+0x60],rcx
   1408eb07b:	4d 89 f8             	mov    r8,r15
   1408eb07e:	4d 29 cf             	sub    r15,r9
   1408eb081:	4c 89 7c 24 70       	mov    QWORD PTR [rsp+0x70],r15
   1408eb086:	49 89 d2             	mov    r10,rdx
   1408eb089:	4d 29 ca             	sub    r10,r9
   1408eb08c:	4c 89 54 24 68       	mov    QWORD PTR [rsp+0x68],r10
   1408eb091:	4d 8d 4a fc          	lea    r9,[r10-0x4]
   1408eb095:	4c 89 4c 24 48       	mov    QWORD PTR [rsp+0x48],r9
   1408eb09a:	49 f7 d9             	neg    r9
   1408eb09d:	49 c1 f9 3f          	sar    r9,0x3f
   1408eb0a1:	49 21 f9             	and    r9,rdi
   1408eb0a4:	49 8d 3c 01          	lea    rdi,[r9+rax*1]
   1408eb0a8:	48 89 bc 24 90 00 00 	mov    QWORD PTR [rsp+0x90],rdi
   1408eb0af:	00
   1408eb0b0:	49 83 ff 38          	cmp    r15,0x38
   1408eb0b4:	4d 89 e9             	mov    r9,r13
   1408eb0b7:	41 bd 38 00 00 00    	mov    r13d,0x38
   1408eb0bd:	4d 0f 4f fd          	cmovg  r15,r13
   1408eb0c1:	4c 8d 9c 24 c8 00 00 	lea    r11,[rsp+0xc8]
   1408eb0c8:	00
   1408eb0c9:	49 39 fb             	cmp    r11,rdi
   1408eb0cc:	74 58                	je     0x1408eb126
   1408eb0ce:	48 89 f8             	mov    rax,rdi
   1408eb0d1:	4c 89 db             	mov    rbx,r11
   1408eb0d4:	4c 89 f9             	mov    rcx,r15
   1408eb0d7:	e8 64 22 79 ff       	call   0x14007d340
   1408eb0dc:	48 8b 84 24 18 01 00 	mov    rax,QWORD PTR [rsp+0x118]
   1408eb0e3:	00
   1408eb0e4:	48 8b 4c 24 60       	mov    rcx,QWORD PTR [rsp+0x60]
   1408eb0e9:	48 8b 54 24 40       	mov    rdx,QWORD PTR [rsp+0x40]
   1408eb0ee:	48 8b 9c 24 80 00 00 	mov    rbx,QWORD PTR [rsp+0x80]
   1408eb0f5:	00
   1408eb0f6:	48 8b 74 24 78       	mov    rsi,QWORD PTR [rsp+0x78]
   1408eb0fb:	48 8b bc 24 90 00 00 	mov    rdi,QWORD PTR [rsp+0x90]
   1408eb102:	00
   1408eb103:	4c 8b 84 24 88 00 00 	mov    r8,QWORD PTR [rsp+0x88]
   1408eb10a:	00
   1408eb10b:	4c 8b 8c 24 20 01 00 	mov    r9,QWORD PTR [rsp+0x120]
   1408eb112:	00
   1408eb113:	4c 8b 54 24 68       	mov    r10,QWORD PTR [rsp+0x68]
   1408eb118:	4c 8b a4 24 10 01 00 	mov    r12,QWORD PTR [rsp+0x110]
   1408eb11f:	00
   1408eb120:	41 bd 38 00 00 00    	mov    r13d,0x38
   1408eb126:	4c 8b 5c 24 48       	mov    r11,QWORD PTR [rsp+0x48]
   1408eb12b:	49 83 fb 38          	cmp    r11,0x38
   1408eb12f:	0f 82 3d 02 00 00    	jb     0x1408eb372
   1408eb135:	0f b6 05 34 77 88 03 	movzx  eax,BYTE PTR [rip+0x3887734]        # 0x144172870
   1408eb13c:	48 8b 1d 35 77 88 03 	mov    rbx,QWORD PTR [rip+0x3887735]        # 0x144172878
   1408eb143:	48 8b 0d 36 77 88 03 	mov    rcx,QWORD PTR [rip+0x3887736]        # 0x144172880
   1408eb14a:	4c 8b 8c 24 a0 00 00 	mov    r9,QWORD PTR [rsp+0xa0]
   1408eb151:	00
   1408eb152:	4c 8b 94 24 a8 00 00 	mov    r10,QWORD PTR [rsp+0xa8]
   1408eb159:	00
   1408eb15a:	4c 89 ee             	mov    rsi,r13
   1408eb15d:	4d 89 d8             	mov    r8,r11
   1408eb160:	e8 bb 47 cc ff       	call   0x1405af920
   1408eb165:	48 85 c0             	test   rax,rax
   1408eb168:	75 65                	jne    0x1408eb1cf
   1408eb16a:	48 8b 4c 24 70       	mov    rcx,QWORD PTR [rsp+0x70]
   1408eb16f:	48 83 f9 38          	cmp    rcx,0x38
   1408eb173:	0f 82 ef 01 00 00    	jb     0x1408eb368
   1408eb179:	4c 8d 59 c8          	lea    r11,[rcx-0x38]
   1408eb17d:	0f 1f 00             	nop    DWORD PTR [rax]
   1408eb180:	49 83 fb 03          	cmp    r11,0x3
   1408eb184:	0f 86 d1 01 00 00    	jbe    0x1408eb35b
   1408eb18a:	4c 8b 5c 24 68       	mov    r11,QWORD PTR [rsp+0x68]
   1408eb18f:	4d 8d 63 c4          	lea    r12,[r11-0x3c]
   1408eb193:	49 f7 dc             	neg    r12
   1408eb196:	49 c1 fc 3f          	sar    r12,0x3f
   1408eb19a:	41 83 e4 38          	and    r12d,0x38
   1408eb19e:	4c 8b 6c 24 60       	mov    r13,QWORD PTR [rsp+0x60]
   1408eb1a3:	4c 8b bc 24 90 00 00 	mov    r15,QWORD PTR [rsp+0x90]
   1408eb1aa:	00
   1408eb1ab:	47 89 2c 27          	mov    DWORD PTR [r15+r12*1],r13d
   1408eb1af:	48 83 f9 3c          	cmp    rcx,0x3c
   1408eb1b3:	0f 82 98 01 00 00    	jb     0x1408eb351
   1408eb1b9:	48 83 c1 c4          	add    rcx,0xffffffffffffffc4
   1408eb1bd:	0f 1f 00             	nop    DWORD PTR [rax]
   1408eb1c0:	48 83 f9 03          	cmp    rcx,0x3
   1408eb1c4:	0f 87 a9 fd ff ff    	ja     0x1408eaf73
   1408eb1ca:	e9 78 01 00 00       	jmp    0x1408eb347
   1408eb1cf:	44 0f 11 bc 24 28 01 	movups XMMWORD PTR [rsp+0x128],xmm15
   1408eb1d6:	00 00
   1408eb1d8:	48 85 c0             	test   rax,rax
   1408eb1db:	74 04                	je     0x1408eb1e1
   1408eb1dd:	48 8b 40 08          	mov    rax,QWORD PTR [rax+0x8]
   1408eb1e1:	48 89 84 24 28 01 00 	mov    QWORD PTR [rsp+0x128],rax
   1408eb1e8:	00
   1408eb1e9:	48 89 9c 24 30 01 00 	mov    QWORD PTR [rsp+0x130],rbx
   1408eb1f0:	00
   1408eb1f1:	48 8d 05 a3 80 05 02 	lea    rax,[rip+0x20580a3]        # 0x14294329b
   1408eb1f8:	bb 0d 00 00 00       	mov    ebx,0xd
   1408eb1fd:	48 8d 8c 24 28 01 00 	lea    rcx,[rsp+0x128]
   1408eb204:	00
   1408eb205:	bf 01 00 00 00       	mov    edi,0x1
   1408eb20a:	48 89 fe             	mov    rsi,rdi
   1408eb20d:	e8 4e be 82 ff       	call   0x140117060
   1408eb212:	31 c9                	xor    ecx,ecx
   1408eb214:	48 89 c7             	mov    rdi,rax
   1408eb217:	48 89 de             	mov    rsi,rbx
   1408eb21a:	31 c0                	xor    eax,eax
   1408eb21c:	48 89 cb             	mov    rbx,rcx
   1408eb21f:	48 81 c4 a0 01 00 00 	add    rsp,0x1a0
   1408eb226:	5d                   	pop    rbp
   1408eb227:	c3                   	ret
   1408eb228:	31 c9                	xor    ecx,ecx
   1408eb22a:	eb 54                	jmp    0x1408eb280
   1408eb22c:	4c 89 44 24 50       	mov    QWORD PTR [rsp+0x50],r8
   1408eb231:	48 89 84 24 98 00 00 	mov    QWORD PTR [rsp+0x98],rax
   1408eb238:	00
   1408eb239:	48 89 54 24 58       	mov    QWORD PTR [rsp+0x58],rdx
   1408eb23e:	48 01 d8             	add    rax,rbx
   1408eb241:	4c 89 cb             	mov    rbx,r9
   1408eb244:	48 89 f9             	mov    rcx,rdi
   1408eb247:	e8 f4 20 79 ff       	call   0x14007d340
   1408eb24c:	4c 8b ac 24 18 01 00 	mov    r13,QWORD PTR [rsp+0x118]
   1408eb253:	00
   1408eb254:	49 83 c5 68          	add    r13,0x68
   1408eb258:	48 8b 8c 24 88 00 00 	mov    rcx,QWORD PTR [rsp+0x88]
   1408eb25f:	00
   1408eb260:	48 ff c1             	inc    rcx
   1408eb263:	4c 8b 9c 24 b8 01 00 	mov    r11,QWORD PTR [rsp+0x1b8]
   1408eb26a:	00
   1408eb26b:	48 8b 54 24 58       	mov    rdx,QWORD PTR [rsp+0x58]
   1408eb270:	48 8b 5c 24 50       	mov    rbx,QWORD PTR [rsp+0x50]
   1408eb275:	48 8b 84 24 98 00 00 	mov    rax,QWORD PTR [rsp+0x98]
   1408eb27c:	00
   1408eb27d:	0f 1f 00             	nop    DWORD PTR [rax]
   1408eb280:	49 39 cb             	cmp    r11,rcx
   1408eb283:	0f 8e ae 00 00 00    	jle    0x1408eb337
   1408eb289:	48 89 8c 24 88 00 00 	mov    QWORD PTR [rsp+0x88],rcx
   1408eb290:	00
   1408eb291:	4c 89 ac 24 18 01 00 	mov    QWORD PTR [rsp+0x118],r13
   1408eb298:	00
   1408eb299:	4d 8b 45 00          	mov    r8,QWORD PTR [r13+0x0]
   1408eb29d:	4c 89 84 24 38 01 00 	mov    QWORD PTR [rsp+0x138],r8
   1408eb2a4:	00
   1408eb2a5:	49 8d 75 08          	lea    rsi,[r13+0x8]
   1408eb2a9:	48 8d bc 24 40 01 00 	lea    rdi,[rsp+0x140]
   1408eb2b0:	00
   1408eb2b1:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
   1408eb2b8:	00 00
   1408eb2ba:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
   1408eb2c0:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
   1408eb2c5:	48 8d 6c 24 f0       	lea    rbp,[rsp-0x10]
   1408eb2ca:	e8 fd 1c 79 ff       	call   0x14007cfcc
   1408eb2cf:	48 8b 6d 00          	mov    rbp,QWORD PTR [rbp+0x0]
   1408eb2d3:	48 8b bc 24 50 01 00 	mov    rdi,QWORD PTR [rsp+0x150]
   1408eb2da:	00
   1408eb2db:	4c 8d 04 1f          	lea    r8,[rdi+rbx*1]
   1408eb2df:	4c 8b 8c 24 48 01 00 	mov    r9,QWORD PTR [rsp+0x148]
   1408eb2e6:	00
   1408eb2e7:	4c 39 c2             	cmp    rdx,r8
   1408eb2ea:	0f 83 3c ff ff ff    	jae    0x1408eb22c
   1408eb2f0:	48 89 5c 24 50       	mov    QWORD PTR [rsp+0x50],rbx
   1408eb2f5:	4c 89 8c 24 08 01 00 	mov    QWORD PTR [rsp+0x108],r9
   1408eb2fc:	00
   1408eb2fd:	48 89 bc 24 80 00 00 	mov    QWORD PTR [rsp+0x80],rdi
   1408eb304:	00
   1408eb305:	4c 89 c3             	mov    rbx,r8
   1408eb308:	48 89 d1             	mov    rcx,rdx
   1408eb30b:	48 8d 35 8e 0c b8 01 	lea    rsi,[rip+0x1b80c8e]        # 0x14246bfa0
   1408eb312:	e8 a9 b0 78 ff       	call   0x1400763c0
   1408eb317:	48 8b bc 24 80 00 00 	mov    rdi,QWORD PTR [rsp+0x80]
   1408eb31e:	00
   1408eb31f:	4c 8b 8c 24 08 01 00 	mov    r9,QWORD PTR [rsp+0x108]
   1408eb326:	00
   1408eb327:	49 89 d8             	mov    r8,rbx
   1408eb32a:	48 89 ca             	mov    rdx,rcx
   1408eb32d:	48 8b 5c 24 50       	mov    rbx,QWORD PTR [rsp+0x50]
   1408eb332:	e9 f5 fe ff ff       	jmp    0x1408eb22c
   1408eb337:	48 89 d1             	mov    rcx,rdx
   1408eb33a:	31 ff                	xor    edi,edi
   1408eb33c:	31 f6                	xor    esi,esi
   1408eb33e:	48 81 c4 a0 01 00 00 	add    rsp,0x1a0
   1408eb345:	5d                   	pop    rbp
   1408eb346:	c3                   	ret
   1408eb347:	b8 03 00 00 00       	mov    eax,0x3
   1408eb34c:	e8 ef 15 79 ff       	call   0x14007c940
   1408eb351:	b8 3c 00 00 00       	mov    eax,0x3c
   1408eb356:	e8 a5 16 79 ff       	call   0x14007ca00
   1408eb35b:	b8 03 00 00 00       	mov    eax,0x3
   1408eb360:	4c 89 d9             	mov    rcx,r11
   1408eb363:	e8 d8 15 79 ff       	call   0x14007c940
   1408eb368:	b8 38 00 00 00       	mov    eax,0x38
   1408eb36d:	e8 8e 16 79 ff       	call   0x14007ca00
   1408eb372:	4c 89 e9             	mov    rcx,r13
   1408eb375:	4c 89 da             	mov    rdx,r11
   1408eb378:	e8 43 16 79 ff       	call   0x14007c9c0
   1408eb37d:	48 89 f8             	mov    rax,rdi
   1408eb380:	48 89 d9             	mov    rcx,rbx
   1408eb383:	e8 78 16 79 ff       	call   0x14007ca00
   1408eb388:	b8 03 00 00 00       	mov    eax,0x3
   1408eb38d:	e8 ae 15 79 ff       	call   0x14007c940
   1408eb392:	90                   	nop
   1408eb393:	48 89 44 24 08       	mov    QWORD PTR [rsp+0x8],rax
   1408eb398:	48 89 5c 24 10       	mov    QWORD PTR [rsp+0x10],rbx
   1408eb39d:	48 89 4c 24 18       	mov    QWORD PTR [rsp+0x18],rcx
   1408eb3a2:	e8 d9 f2 78 ff       	call   0x14007a680
   1408eb3a7:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
   1408eb3ac:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
   1408eb3b1:	48 8b 4c 24 18       	mov    rcx,QWORD PTR [rsp+0x18]
   1408eb3b6:	e9 45 fa ff ff       	jmp    0x1408eae00
   1408eb3bb:	cc                   	int3
   1408eb3bc:	cc                   	int3
   1408eb3bd:	cc                   	int3
   1408eb3be:	cc                   	int3
   1408eb3bf:	cc                   	int3
