
rf_online.bin:     file format pei-i386


Disassembly of section .text:

007a0f30 <.text+0x39ff30>:
  7a0f30:	55                   	push   ebp
  7a0f31:	8b ec                	mov    ebp,esp
  7a0f33:	6a ff                	push   0xffffffff
  7a0f35:	68 e8 b9 ae 00       	push   0xaeb9e8
  7a0f3a:	64 a1 00 00 00 00    	mov    eax,fs:0x0
  7a0f40:	50                   	push   eax
  7a0f41:	51                   	push   ecx
  7a0f42:	83 ec 50             	sub    esp,0x50
  7a0f45:	53                   	push   ebx
  7a0f46:	56                   	push   esi
  7a0f47:	57                   	push   edi
  7a0f48:	a1 dc 2e c0 00       	mov    eax,ds:0xc02edc
  7a0f4d:	33 c5                	xor    eax,ebp
  7a0f4f:	50                   	push   eax
  7a0f50:	8d 45 f4             	lea    eax,[ebp-0xc]
  7a0f53:	64 a3 00 00 00 00    	mov    fs:0x0,eax
  7a0f59:	89 65 f0             	mov    DWORD PTR [ebp-0x10],esp
  7a0f5c:	50                   	push   eax
  7a0f5d:	53                   	push   ebx
  7a0f5e:	51                   	push   ecx
  7a0f5f:	8d 45 08             	lea    eax,[ebp+0x8]
  7a0f62:	8d 5d 0c             	lea    ebx,[ebp+0xc]
  7a0f65:	74 06                	je     0x7a0f6d
  7a0f67:	75 04                	jne    0x7a0f6d
  7a0f69:	e8 61 68 33 68       	call   0x68ad77cf
  7a0f6e:	9a 0f 7a 00 c3 66 75 	call   0x7566:0xc3007a0f
  7a0f75:	3d e9 63 63 66       	cmp    eax,0x666363e9
  7a0f7a:	77 34                	ja     0x7a0fb0
  7a0f7c:	e0 64                	loopne 0x7a0fe2
  7a0f7e:	60                   	pusha
  7a0f7f:	66 72 3e             	data16 jb 0x7a0fc0
  7a0f82:	e1 66                	loope  0x7a0fea
  7a0f84:	68 66 73 3d ea       	push   0xea3d7366
  7a0f89:	6f                   	outs   dx,DWORD PTR ds:[esi]
  7a0f8a:	6b e0 64             	imul   esp,eax,0x64
  7a0f8d:	60                   	pusha
  7a0f8e:	66 72 3e             	data16 jb 0x7a0fcf
  7a0f91:	e1 66                	loope  0x7a0ff9
  7a0f93:	68 66 73 3d ea       	push   0xea3d7366
  7a0f98:	6f                   	outs   dx,DWORD PTR ds:[esi]
  7a0f99:	6b 59 5b 58          	imul   ebx,DWORD PTR [ecx+0x5b],0x58
  7a0f9d:	68 80 09 7a 00       	push   0x7a0980
  7a0fa2:	e8 16 cc 01 00       	call   0x7bdbbd
  7a0fa7:	83 c4 04             	add    esp,0x4
  7a0faa:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  7a0fad:	50                   	push   eax
  7a0fae:	8d 4d ec             	lea    ecx,[ebp-0x14]
  7a0fb1:	e8 fa 16 00 00       	call   0x7a26b0
  7a0fb6:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [ebp-0x4],0x0
  7a0fbd:	83 3d 08 ea 4d 02 00 	cmp    DWORD PTR ds:0x24dea08,0x0
  7a0fc4:	75 0c                	jne    0x7a0fd2
  7a0fc6:	c7 05 08 ea 4d 02 01 	mov    DWORD PTR ds:0x24dea08,0x1
  7a0fcd:	00 00 00
  7a0fd0:	eb 0f                	jmp    0x7a0fe1
  7a0fd2:	e8 09 ff ff ff       	call   0x7a0ee0
  7a0fd7:	c7 05 08 ea 4d 02 01 	mov    DWORD PTR ds:0x24dea08,0x1
  7a0fde:	00 00 00
  7a0fe1:	c6 45 fc 01          	mov    BYTE PTR [ebp-0x4],0x1
  7a0fe5:	e8 d6 fb ff ff       	call   0x7a0bc0
  7a0fea:	89 45 e8             	mov    DWORD PTR [ebp-0x18],eax
  7a0fed:	83 7d e8 00          	cmp    DWORD PTR [ebp-0x18],0x0
  7a0ff1:	7d 27                	jge    0x7a101a
  7a0ff3:	c7 05 08 ea 4d 02 00 	mov    DWORD PTR ds:0x24dea08,0x0
  7a0ffa:	00 00 00
  7a0ffd:	8b                   	.byte 0x8b
  7a0ffe:	4d                   	dec    ebp
