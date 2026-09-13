// 100a43468 FUN_100a43468

byte FUN_100a43468(undefined8 param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puVar2;
  undefined *puVar3;
  void *aBlock;
  undefined *puVar4;
  byte bVar5;
  ID unaff_x20;
  undefined8 uVar6;
  undefined *local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  code *local_68;
  undefined *local_60;
  undefined2 local_52;
  
  local_52 = 0;
  uVar6 = *(undefined8 *)PTR__NSStrikethroughStyleAttributeName_100ddae40;
  puVar2 = &DAT_100e43520;
  _swift_allocObject(&DAT_100e43520,0x20,7);
  *(long *)(puVar2 + 0x10) = (long)&local_52 + 1;
  *(undefined2 **)(puVar2 + 0x18) = &local_52;
  puVar3 = &DAT_100e43548;
  _swift_allocObject(&DAT_100e43548,0x20,7);
  *(code **)(puVar3 + 0x10) = thunk_FUN_100a47994;
  *(undefined **)(puVar3 + 0x18) = puVar2;
  local_68 = thunk_FUN_100074b40;
  local_88 = PTR___NSConcreteStackBlock_100ddc728;
  local_80 = DAT_100b80ea0;
  local_78 = FUN_100a430a8;
  puStack_70 = &DAT_100e43560;
  local_60 = puVar3;
  aBlock = __Block_copy(&local_88);
  puVar4 = local_60;
  _swift_retain(puVar3);
  _swift_release(puVar4);
  _objc_msgSend(unaff_x20,PTR_s_enumerateAttribute_inRange_optio_100eedcb0,uVar6,param_1,param_2,0,
                aBlock);
  __Block_release(aBlock);
  puVar4 = puVar3;
  _swift_isEscapingClosureAtFileLocation(puVar3,"",0x70,100,0x49,1);
  _swift_release(puVar3);
  if (((ulong)puVar4 & 1) == 0) {
    if (local_52._1_1_ == '\x01') {
      bVar5 = (byte)local_52;
      _swift_release(puVar2);
      bVar5 = bVar5 ^ 1;
    }
    else {
      _swift_release(puVar2);
      bVar5 = 0;
    }
    return bVar5 & 1;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x100a435ec);
  (*pcVar1)();
}

