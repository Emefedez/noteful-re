// 100adf3d8 FUN_100adf3d8

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x000100adf84c) */
/* WARNING: Removing unreachable block (ram,0x000100adf5e8) */

void FUN_100adf3d8(undefined8 param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  URL UVar6;
  undefined *puVar7;
  undefined1 *self;
  ID IVar8;
  Data DVar9;
  Data DVar10;
  long lVar11;
  undefined *puVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  ulong uVar16;
  long extraout_x8;
  long unaff_x20;
  long unaff_x21;
  long lVar17;
  code *pcVar18;
  undefined1 auStack_140 [8];
  undefined8 *local_138;
  undefined *local_130;
  long local_128;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8 [15];
  long local_70;
  
  local_70 = *(long *)PTR____stack_chk_guard_100ddc7d0;
  UVar6 = Foundation::URL::typeMetadataAccessor();
  lVar17 = *(long *)(UVar6.unknown + -8);
  (*(code *)PTR____chkstk_darwin_100ddc798)(*(undefined8 *)(lVar17 + 0x40));
  puVar12 = PTR___swiftEmptyArrayStorage_100dde690;
  self = auStack_140 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0);
  puVar14 = (undefined8 *)(unaff_x20 + _TtC10NotesStore17PackageFileReader::toc);
  puVar7 = PTR___swiftEmptyArrayStorage_100dde690;
  FUN_100991eb8();
  *(undefined4 *)puVar14 = 0x3f9ae148;
  puVar14[1] = puVar12;
  puVar14[2] = puVar12;
  puVar14[3] = puVar12;
  puVar14[4] = puVar12;
  puVar14[5] = puVar7;
  lVar5 = _TtC10NotesStore17PackageFileReader::url;
  pcVar18 = *(code **)(lVar17 + 0x10);
  (*pcVar18)(unaff_x20 + _TtC10NotesStore17PackageFileReader::url,param_1,UVar6.unknown);
  FUN_100a03f48(0);
  (*pcVar18)(self,param_1,UVar6.unknown);
  FUN_100adefbc(self,&PTR_s_fileHandleForReadingFromURL_erro_100ef07e0);
  lVar11 = _TtC10NotesStore17PackageFileReader::handle;
  if (unaff_x21 != 0) {
    pcVar18 = *(code **)(lVar17 + 8);
    (*pcVar18)(param_1,UVar6.unknown);
    (*pcVar18)(unaff_x20 + lVar5,UVar6.unknown);
    lVar11 = unaff_x20 + _TtC10NotesStore17PackageFileReader::toc;
    uVar1 = *(undefined8 *)(lVar11 + 8);
    uVar3 = *(undefined8 *)(lVar11 + 0x10);
    uVar2 = *(undefined8 *)(lVar11 + 0x18);
    uVar4 = *(undefined8 *)(lVar11 + 0x20);
    _swift_bridgeObjectRelease(*(undefined8 *)(lVar11 + 0x28));
    _swift_bridgeObjectRelease(uVar4);
    _swift_bridgeObjectRelease(uVar2);
    _swift_bridgeObjectRelease(uVar3);
    _swift_bridgeObjectRelease(uVar1);
    FUN_100ae099c(0);
    _swift_deallocPartialClassInstance();
    goto LAB_100adf7c0;
  }
  *(undefined1 **)(unaff_x20 + _TtC10NotesStore17PackageFileReader::handle) = self;
  IVar8 = _objc_msgSend((ID)self,PTR_s_seekToEndOfFile_100ef43d0);
  if (IVar8 < 0x10) {
                    /* WARNING: Does not return */
    pcVar18 = (code *)SoftwareBreakpoint(1,0x100adf950);
    (*pcVar18)();
  }
  _objc_msgSend(*(ID *)(unaff_x20 + lVar11),PTR_s_seekToFileOffset__100ef43d8,IVar8 - 0x10);
  uVar16 = 0x10;
  puVar12 = PTR_s_readDataOfLength__100ef3790;
  DVar9.unknown =
       (undefined *)
       _objc_msgSend(*(ID *)(unaff_x20 + lVar11),PTR_s_readDataOfLength__100ef3790,0x10);
  DVar10 = Foundation::Data::__unconditionallyBridgeFromObjectiveC(DVar9);
  FUN_1000266a8(DVar10.unknown,puVar12);
  DVar9 = DVar10;
  puVar7 = puVar12;
  FUN_100ae186c();
  if ((int)DVar9.unknown == -0x55443322) {
    if ((long)puVar7 < 0) {
                    /* WARNING: Does not return */
      pcVar18 = (code *)SoftwareBreakpoint(1,0x100adf954);
      (*pcVar18)();
    }
    local_e8[0] = 0;
    local_128 = unaff_x21;
    IVar8 = _objc_msgSend(*(ID *)(unaff_x20 + lVar11),PTR_s_seekToOffset_error__100eedec8,puVar7,
                          local_e8);
    if ((int)IVar8 == 0) {
      Foundation::__convertNSErrorToError();
      goto LAB_100adf790;
    }
    puVar7 = PTR_s_readDataOfLength__100ef3790;
    local_138 = puVar14;
    local_130 = puVar12;
    DVar9.unknown =
         (undefined *)
         _objc_msgSend(*(ID *)(unaff_x20 + lVar11),PTR_s_readDataOfLength__100ef3790,
                       uVar16 & 0xffffffff);
    DVar9 = Foundation::Data::__unconditionallyBridgeFromObjectiveC(DVar9);
    lVar11 = 0;
    FUN_100ae8848();
    _swift_initStackObject();
    puVar12 = PTR___swiftEmptyArrayStorage_100dde690;
    FUN_100991d8c();
    *(undefined **)(lVar11 + 0x18) = puVar7;
    *(undefined **)(lVar11 + 0x20) = puVar12;
    *(undefined1 *)(lVar11 + 0x28) = 0;
    *(undefined8 *)(lVar11 + 0x30) = 0;
    *(undefined8 *)(lVar11 + 0x38) = 0;
    *(undefined1 *)(lVar11 + 0x40) = 1;
    *(undefined **)(lVar11 + 0x10) = DVar9.unknown;
    *(undefined8 *)(lVar11 + 0x50) = 0;
    *(undefined8 *)(lVar11 + 0x58) = 0;
    *(undefined8 *)(lVar11 + 0x48) = 0;
    FUN_1000266a8(DVar9.unknown,puVar7);
    _swift_retain(lVar11);
    FUN_100a557bc(DVar9.unknown,puVar7,lVar11);
    if (local_128 == 0) {
      FUN_100ae197c(&local_118,lVar11);
      (**(code **)(lVar17 + 8))(param_1,UVar6.unknown);
      FUN_100026668(DVar10.unknown,local_130);
      FUN_100026668(DVar9.unknown,puVar7);
      _swift_setDeallocating(lVar11);
      FUN_100026668(*(undefined8 *)(lVar11 + 0x10),*(undefined8 *)(lVar11 + 0x18));
      _swift_bridgeObjectRelease(*(undefined8 *)(lVar11 + 0x20));
      _swift_bridgeObjectRelease(*(undefined8 *)(lVar11 + 0x58));
      puVar14 = local_138;
      _swift_beginAccess(local_138,local_e8,1,0);
      uVar1 = puVar14[1];
      uVar3 = puVar14[2];
      uVar2 = puVar14[3];
      uVar4 = puVar14[4];
      uVar15 = puVar14[5];
      puVar14[1] = uStack_110;
      *puVar14 = local_118;
      puVar14[3] = uStack_100;
      puVar14[2] = local_108;
      puVar14[5] = uStack_f0;
      puVar14[4] = local_f8;
      _swift_bridgeObjectRelease(uVar15);
      _swift_bridgeObjectRelease(uVar4);
      _swift_bridgeObjectRelease(uVar2);
      _swift_bridgeObjectRelease(uVar3);
      _swift_bridgeObjectRelease(uVar1);
      goto LAB_100adf7c0;
    }
    FUN_100026668(DVar9.unknown,puVar7);
    FUN_100026668(DVar10.unknown,local_130);
    (**(code **)(lVar17 + 8))(param_1,UVar6.unknown);
    _swift_setDeallocating(lVar11);
    FUN_100026668(*(undefined8 *)(lVar11 + 0x10),*(undefined8 *)(lVar11 + 0x18));
    _swift_bridgeObjectRelease(*(undefined8 *)(lVar11 + 0x20));
    _swift_bridgeObjectRelease(*(undefined8 *)(lVar11 + 0x58));
  }
  else {
    puVar13 = (undefined8 *)0x0;
    FUN_100ae099c();
    puVar14 = puVar13;
    FUN_1007ebfa8();
    _swift_allocError(&DAT_100e4a268,puVar14,0,0);
    *puVar14 = puVar13;
    puVar14[1] = 0;
    *(undefined2 *)(puVar14 + 2) = 0;
    *(undefined1 *)((long)puVar14 + 0x12) = 0;
LAB_100adf790:
    _swift_willThrow();
    FUN_100026668(DVar10.unknown,puVar12);
    (**(code **)(lVar17 + 8))(param_1,UVar6.unknown);
  }
  _swift_release();
LAB_100adf7c0:
  if (*(long *)PTR____stack_chk_guard_100ddc7d0 != local_70) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

