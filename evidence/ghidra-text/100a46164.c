// 100a46164 FUN_100a46164

/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 FUN_100a46164(undefined8 param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined *puVar2;
  undefined *puVar3;
  void *aBlock;
  undefined *puVar4;
  NSNumber *pNVar5;
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
  puVar2 = &DAT_100e43d18;
  _swift_allocObject(&DAT_100e43d18,0x20,7);
  *(long *)(puVar2 + 0x10) = (long)&local_52 + 1;
  *(undefined2 **)(puVar2 + 0x18) = &local_52;
  puVar3 = &DAT_100e43d40;
  _swift_allocObject(&DAT_100e43d40,0x20,7);
  *(code **)(puVar3 + 0x10) = thunk_FUN_100a47994;
  *(undefined **)(puVar3 + 0x18) = puVar2;
  local_68 = thunk_FUN_100074b40;
  local_88 = PTR___NSConcreteStackBlock_100ddc728;
  local_80 = DAT_100b80ea0;
  local_78 = FUN_100a430a8;
  puStack_70 = &DAT_100e43d58;
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
    if ((local_52 & 0x100) == 0) {
      _swift_release(puVar2);
    }
    else {
      _swift_release(puVar2);
    }
    pNVar5 = (extension_Foundation)::__int64::_bridgeToObjectiveC();
    _objc_msgSend(unaff_x20,PTR_s_addAttribute_value_range__100eebb58,uVar6,pNVar5,param_1,param_2);
    return 0;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x100a46310);
  (*pcVar1)();
}

