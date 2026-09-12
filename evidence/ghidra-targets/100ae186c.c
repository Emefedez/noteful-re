// 100ae186c FUN_100ae186c

void FUN_100ae186c(undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  undefined *puVar2;
  undefined1 auStack_e0 [16];
  undefined4 *local_d0;
  long lStack_c8;
  undefined8 *local_c0;
  undefined4 *puStack_b8;
  undefined4 local_a4;
  undefined8 local_a0;
  undefined4 local_94 [25];
  
  lVar1 = 0;
  FUN_100ae8848();
  _swift_initStackObject();
  puVar2 = PTR___swiftEmptyArrayStorage_100dde690;
  FUN_100991d8c();
  *(undefined8 *)(lVar1 + 0x18) = param_2;
  *(undefined **)(lVar1 + 0x20) = puVar2;
  *(undefined1 *)(lVar1 + 0x28) = 0;
  *(undefined8 *)(lVar1 + 0x30) = 0;
  *(undefined8 *)(lVar1 + 0x38) = 0;
  *(undefined1 *)(lVar1 + 0x40) = 1;
  *(undefined8 *)(lVar1 + 0x10) = param_1;
  *(undefined8 *)(lVar1 + 0x50) = 0;
  *(undefined8 *)(lVar1 + 0x58) = 0;
  *(undefined8 *)(lVar1 + 0x48) = 0;
  local_94[0] = 0;
  local_a0 = 0;
  local_a4 = 0;
  local_d0 = local_94;
  local_c0 = &local_a0;
  puStack_b8 = &local_a4;
  lStack_c8 = lVar1;
  FUN_1000266a8(param_1,param_2);
  _swift_retain(lVar1);
  FUN_100ae1678(param_1,param_2,lVar1,FUN_100ae20dc,auStack_e0);
  FUN_100026668(param_1,param_2);
  _swift_setDeallocating(lVar1);
  FUN_100026668(*(undefined8 *)(lVar1 + 0x10),*(undefined8 *)(lVar1 + 0x18));
  _swift_bridgeObjectRelease(*(undefined8 *)(lVar1 + 0x20));
  _swift_bridgeObjectRelease(*(undefined8 *)(lVar1 + 0x58));
  return;
}

