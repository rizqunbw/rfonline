/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008217c0(void)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  bool bVar5;
  double dVar6;
  long local_118;
  undefined4 local_114 [4];
  CHAR local_104 [256];
  uint local_4;

  local_4 = DAT_00c02edc ^ (uint)&local_118;
  _memset(&DAT_02514860,0,0xc6c);
  _DAT_02514ff8 = _DAT_00b3d628;
  _DAT_0251485c = 1;
  _DAT_02514fe4 = _DAT_00b00d3c;
  DAT_02515098 = 0;
  DAT_02515084 = 0;
  _DAT_02514fe8 = _DAT_00b3d624;
  _DAT_025150a4 = 0;
  _DAT_025150b8 = 0;
  _DAT_02514ff4 = _DAT_00b20f60;
  _DAT_02514ff0 = _DAT_00b20f60;
  DAT_02514fec = _DAT_00b06478;
  DAT_02515320 = 0;
  DAT_0251531c = 0;
  DAT_02515318 = 0;
  _DAT_02515314 = 0;
  DAT_0251530c = 0;
  DAT_02515308 = 0;
  _DAT_02515304 = 0;
  _DAT_02515300 = 0;
  _DAT_025152f8 = 0;
  _DAT_025152f4 = 0;
  _DAT_025152f0 = 0;
  DAT_025152ec = 0;
  _DAT_02515324 = 0x3f800000;
  DAT_02515310 = 0x3f800000;
  _DAT_025152fc = 0x3f800000;
  DAT_025152e8 = 0x3f800000;
  _DAT_025152e4 = 0x3f800000;
  _DAT_025152d0 = 0x3f800000;
  _DAT_025152bc = 0x3f800000;
  _DAT_025152a8 = 0x3f800000;
  _DAT_025153e4 = 0x3f800000;
  _DAT_025153d0 = 0x3f800000;
  _DAT_025153bc = 0x3f800000;
  DAT_025153a8 = 0x3f800000;
  _DAT_025152e0 = 0;
  _DAT_025152dc = 0;
  _DAT_025152d8 = 0;
  _DAT_025152d4 = 0;
  _DAT_025152cc = 0;
  _DAT_025152c8 = 0;
  _DAT_025152c4 = 0;
  _DAT_025152c0 = 0;
  _DAT_025152b8 = 0;
  _DAT_025152b4 = 0;
  _DAT_025152b0 = 0;
  _DAT_025152ac = 0;
  _DAT_025153e0 = 0;
  _DAT_025153dc = 0;
  _DAT_025153d8 = 0;
  _DAT_025153d4 = 0;
  _DAT_025153cc = 0;
  _DAT_025153c8 = 0;
  _DAT_025153c4 = 0;
  _DAT_025153c0 = 0;
  _DAT_025153b8 = 0;
  _DAT_025153b4 = 0;
  _DAT_025153b0 = 0;
  DAT_025153ac = 0;
  _DAT_02515090 = 0;
  _DAT_02515094 = 0;
  _DAT_025150a8 = 0;
  _DAT_025150b0 = 0;
  _DAT_025150ac = 0;
  _DAT_025150b4 = 0;
  _DAT_025150bc = 0;
  _DAT_02515038 = 1.0;
  DAT_0251508c = 0;
  _DAT_0251507c = 0x40000;
  _DAT_02515004 = _DAT_00b008f8;
  DAT_0251502c = 0;
  DAT_02515030 = 0;
  DAT_0251519c = 1;
  DAT_02515420 = 0;
  DAT_02515410 = 0;
  DAT_02515414 = 0;
  DAT_02515418 = 0;
  DAT_0251541c = 0;
  DAT_02515498 = 0;
  DAT_02514858 = FUN_0084ee00(0x40000);
  DAT_0251514c = 0xffffffff;
  DAT_02515150 = 0x3f800000;
  DAT_02515154 = 0x3f800000;
  DAT_02515158 = 0x3f800000;
  DAT_0251515c = 0x3f800000;
  DAT_02515160 = 0x3f800000;
  DAT_02515164 = 0x3f800000;
  DAT_02515168 = 0x3f800000;
  DAT_0251516c = 0x3f800000;
  DAT_02515170 = 0x3f800000;
  DAT_02515174 = 0x3f800000;
  DAT_02515178 = 0x3f800000;
  DAT_0251517c = 0x3f800000;
  DAT_02515180 = 0x3f800000;
  DAT_02515184 = 0x3f800000;
  DAT_02515188 = 0x3f800000;
  _DAT_0251518c = 0x3f800000;
  GetPrivateProfileStringA("Path","MapPath",".\\Map\\",&DAT_02514860,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA("Path","SystemPath",".\\System\\",&DAT_025148e0,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("Path","EntityPath",".\\Map\\Entity\\",&DAT_02514960,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA("Path","EffectPath",".\\Effect\\",&DAT_025149e0,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("Path","ScreenShotsPath",".\\ScreenShots\\",&DAT_02514a60,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA("Path","SoundPath",".\\Snd\\",&DAT_02514ae0,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA("RenderState","ScreenXSize","1024",local_104,0x80,".\\R3Engine.ini");
  local_118 = _atol(local_104);
  DAT_02514ffc = (float)local_118;
  DAT_02515424 = 0;
  DAT_0251542c = FUN_007b15c0();
  GetPrivateProfileStringA("RenderState","ScreenYSize","768",local_104,0x80,".\\R3Engine.ini");
  local_118 = _atol(local_104);
  DAT_02515000 = (float)local_118;
  DAT_02515428 = 0;
  DAT_02515430 = FUN_007b15c0();
  GetPrivateProfileStringA("RenderState","RenderBits","32",local_104,0x80,".\\R3Engine.ini");
  DAT_02515008 = _atol(local_104);
  GetPrivateProfileStringA("RenderState","ZbufferBits","24",local_104,0x80,".\\R3Engine.ini");
  DAT_0251500c = _atol(local_104);
  GetPrivateProfileStringA("RenderState","bFullScreen","FALSE",local_104,0x80,".\\R3Engine.ini");
  __strupr(local_104);
  iVar2 = 5;
  bVar5 = true;
  pcVar3 = local_104;
  pcVar4 = "TRUE";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  DAT_02515010 = (uint)bVar5;
  GetPrivateProfileStringA("RenderState","BBoShasi","2",local_104,0x80,".\\R3Engine.ini");
  DAT_02515070 = _atol(local_104);
  GetPrivateProfileStringA("RenderState","TextureDetail","2",local_104,0x80,".\\R3Engine.ini");
  uVar1 = _atol(local_104);
  uVar1 = -(uint)(uVar1 != 0) & uVar1;
  if (2 < uVar1) {
    uVar1 = 3;
  }
  DAT_0251503c = -uVar1 + 3;
  uVar1 = -uVar1 + 2;
  DAT_02515044 = ((int)uVar1 < 0) - 1 & uVar1;
  GetPrivateProfileStringA("RenderState","DynamicLight","1",local_104,0x80,".\\R3Engine.ini");
  _DAT_0251504c = _atol(local_104);
  _DAT_0251504c = -(uint)(_DAT_0251504c != 0) & _DAT_0251504c;
  if (_DAT_0251504c < 3) {
    if (_DAT_0251504c == 1) {
      _DAT_0251504c = 3;
    }
    else if (_DAT_0251504c == 2) {
      _DAT_0251504c = 6;
    }
  }
  else {
    _DAT_0251504c = 10;
  }
  GetPrivateProfileStringA("RenderState","ShadowDetail","1",local_104,0x80,".\\R3Engine.ini");
  uVar1 = _atol(local_104);
  DAT_02515048 = -(uint)(uVar1 != 0) & uVar1;
  if (DAT_02515048 < 3) {
    if ((DAT_02515048 != 1) && (DAT_02515048 == 2)) {
      DAT_02515048 = 10;
    }
  }
  else {
    DAT_02515048 = 0xffffffff;
  }
  GetPrivateProfileStringA("RenderState","bDetailTexture","TRUE",local_104,0x80,".\\R3Engine.ini");
  bVar5 = true;
  iVar2 = 5;
  pcVar3 = local_104;
  pcVar4 = "TRUE";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  DAT_02515040 = (uint)bVar5;
  GetPrivateProfileStringA("RenderState","bMouseAccelation","TRUE",local_104,0x80,".\\R3Engine.ini")
  ;
  __strupr(local_104);
  local_114[0] = _DAT_00b20f60;
  bVar5 = true;
  local_114[1] = _DAT_00b01620;
  iVar2 = 5;
  local_114[2] = 0x3f800000;
  pcVar3 = local_104;
  pcVar4 = "TRUE";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  DAT_02515068 = (uint)bVar5;
  local_114[3] = 0;
  GetPrivateProfileStringA("RenderState","SeeDistance","2",local_104,0x80,".\\R3Engine.ini");
  uVar1 = _atol(local_104);
  uVar1 = -(uint)(uVar1 != 0) & uVar1;
  if (1 < uVar1) {
    uVar1 = 2;
  }
  _DAT_02515050 = local_114[uVar1];
  GetPrivateProfileStringA("Sound","Sound","TRUE",local_104,0x80,".\\R3Engine.ini");
  __strupr(local_104);
  bVar5 = true;
  iVar2 = 5;
  pcVar3 = local_104;
  pcVar4 = "TRUE";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  DAT_02515054 = (uint)bVar5;
  GetPrivateProfileStringA("Sound","Music","TRUE",local_104,0x80,".\\R3Engine.ini");
  __strupr(local_104);
  bVar5 = true;
  iVar2 = 5;
  pcVar3 = local_104;
  pcVar4 = "TRUE";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  DAT_02515058 = (uint)bVar5;
  GetPrivateProfileStringA("Sound","MusicVol","1.0f",local_104,0x80,".\\R3Engine.ini");
  dVar6 = _atof(local_104);
  _DAT_02515060 = (float)dVar6;
  FUN_0081a7f0(_DAT_02515060);
  GetPrivateProfileStringA("Sound","SoundVol","1.0f",local_104,0x80,".\\R3Engine.ini");
  dVar6 = _atof(local_104);
  _DAT_0251505c = (float)dVar6;
  FUN_0081a7d0(_DAT_0251505c);
  GetPrivateProfileStringA("Sound","AmbVol","1.0f",local_104,0x80,".\\R3Engine.ini");
  dVar6 = _atof(local_104);
  _DAT_02515064 = (float)dVar6;
  FUN_0081a810(_DAT_02515064);
  GetPrivateProfileStringA("RenderState","Gamma","1.0f",local_104,0x80,".\\R3Engine.ini");
  dVar6 = _atof(local_104);
  _DAT_02515038 = (float)dVar6;
  FUN_008215b0(_DAT_02515038,0);
  GetPrivateProfileStringA("RenderState","bStartCamera","FALSE",local_104,0x80,".\\R3Engine.ini");
  __strupr(local_104);
  bVar5 = true;
  iVar2 = 5;
  pcVar3 = local_104;
  pcVar4 = "TRUE";
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar3 == *pcVar4;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  DAT_02514fe0 = (uint)bVar5;
  GetPrivateProfileStringA
            ("SampleCharacter","CharPath",".\\Character\\",&DAT_02514b60,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","CharTexturePath",".\\Character\\tex\\",&DAT_02514be0,0x80,
             ".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","MeshName","SNWG_001.msh",&DAT_02514c60,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","BoneName","bone_b.bn",&DAT_02514ce0,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","StopAni","Stop.ani",&DAT_02514d60,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","RunAni","Run_Loop.ani",&DAT_02514de0,0x80,".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","SwordAni",(LPCSTR)&PTR_00afffb4,&DAT_02514e60,0x80,".\\R3Engine.ini"
            );
  GetPrivateProfileStringA
            ("SampleCharacter","SwordMesh",(LPCSTR)&PTR_00afffb4,&DAT_02514ee0,0x80,
             ".\\R3Engine.ini");
  GetPrivateProfileStringA
            ("SampleCharacter","SwordTexturePath",(LPCSTR)&PTR_00afffb4,&DAT_02514f60,0x80,
             ".\\R3Engine.ini");
  local_114[0] = 0x3f800000;
  local_114[1] = 0x3f800000;
  local_114[2] = 0x3f800000;
  FUN_00820be0(local_114);
  __security_check_cookie(local_4 ^ (uint)&local_118);
  return;
}
