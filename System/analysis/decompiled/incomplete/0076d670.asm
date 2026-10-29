
rf_online.bin:     file format pei-i386


Disassembly of section .text:

0076d670 <.text+0x36c670>:
  76d670:	55                   	push   ebp
  76d671:	8b ec                	mov    ebp,esp
  76d673:	83 ec 44             	sub    esp,0x44
  76d676:	53                   	push   ebx
  76d677:	56                   	push   esi
  76d678:	57                   	push   edi
  76d679:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [ebp-0x4],0x0
  76d680:	e8 eb 01 00 00       	call   0x76d870
  76d685:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  76d688:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  76d68b:	50                   	push   eax
  76d68c:	e8 4f 05 00 00       	call   0x76dbe0
  76d691:	83 c4 04             	add    esp,0x4
  76d694:	85 c0                	test   eax,eax
  76d696:	75 05                	jne    0x76d69d
  76d698:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  76d69b:	eb 20                	jmp    0x76d6bd
  76d69d:	e8 7e 01 00 00       	call   0x76d820
  76d6a2:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  76d6a5:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  76d6a8:	50                   	push   eax
  76d6a9:	e8 32 05 00 00       	call   0x76dbe0
  76d6ae:	83 c4 04             	add    esp,0x4
  76d6b1:	85 c0                	test   eax,eax
  76d6b3:	75 05                	jne    0x76d6ba
  76d6b5:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  76d6b8:	eb 03                	jmp    0x76d6bd
  76d6ba:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  76d6bd:	5f                   	pop    edi
  76d6be:	5e                   	pop    esi
  76d6bf:	5b                   	pop    ebx
  76d6c0:	8b e5                	mov    esp,ebp
  76d6c2:	5d                   	pop    ebp
  76d6c3:	c3                   	ret
