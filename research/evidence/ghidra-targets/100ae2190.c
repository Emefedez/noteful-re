// 100ae2190 FUN_100ae2190

/* WARNING: Function: _objc_opt_self replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Removing unreachable block (ram,0x000100ae25ec) */
/* WARNING: Removing unreachable block (ram,0x000100ae269c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100ae2190(long param_1,undefined *param_2)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  uint uVar6;
  _CocoaArrayWrapper _Var7;
  Data DVar8;
  URL UVar9;
  undefined *puVar10;
  URL self;
  NSString *pNVar11;
  ID self_00;
  NSData *pNVar12;
  undefined *puVar13;
  long extraout_x8;
  int iVar14;
  ulong uVar15;
  uint uVar16;
  long unaff_x20;
  long unaff_x21;
  long lVar17;
  long lVar18;
  code *pcVar19;
  long lVar20;
  ulong uVar21;
  String SVar22;
  long local_d0;
  long local_c8;
  undefined4 local_a4;
  _CocoaArrayWrapper local_a0 [5];
  Data local_78;
  ulong uStack_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_100ddc7d0;
  UVar9 = Foundation::URL::typeMetadataAccessor();
  lVar18 = *(long *)(UVar9.unknown + -8);
  (*(code *)PTR____chkstk_darwin_100ddc798)(*(undefined8 *)(lVar18 + 0x40));
  puVar13 = PTR___swiftEmptyArrayStorage_100dde690;
  lVar17 = (long)&local_d0 - (extraout_x8 + 0xfU & 0xfffffffffffffff0);
  puVar1 = (undefined4 *)(unaff_x20 + _TtC10NotesStore17PackageFileWriter::toc);
  puVar10 = PTR___swiftEmptyArrayStorage_100dde690;
  FUN_100991eb8();
  *puVar1 = 0x3f9ae148;
  *(undefined **)(puVar1 + 2) = puVar13;
  *(undefined **)(puVar1 + 4) = puVar13;
  *(undefined **)(puVar1 + 6) = puVar13;
  *(undefined **)(puVar1 + 8) = puVar13;
  *(undefined **)(puVar1 + 10) = puVar10;
  local_d0 = _TtC10NotesStore17PackageFileWriter::offset;
  *(undefined8 *)(unaff_x20 + _TtC10NotesStore17PackageFileWriter::offset) = 0;
  puVar1 = (undefined4 *)(unaff_x20 + _TtC10NotesStore17PackageFileWriter::footer);
  *puVar1 = 0xaabbccde;
  *(undefined8 *)(puVar1 + 2) = 0xffffffffffffffff;
  puVar1[4] = 0;
  pcVar19 = *(code **)(lVar18 + 0x10);
  local_c8 = _TtC10NotesStore17PackageFileWriter::url;
  (*pcVar19)(unaff_x20 + _TtC10NotesStore17PackageFileWriter::url,param_1,UVar9.unknown);
  self.unknown = (undefined *)
                 _objc_msgSend(PTR__OBJC_CLASS___NSFileManager_100efb2f8,
                               PTR_s_defaultManager_100eefc70);
  SVar22 = Foundation::URL::get_path(self);
  pNVar11 = (extension_Foundation)::Swift::String::_bridgeToObjectiveC();
  _swift_bridgeObjectRelease(SVar22.bridgeObject);
  _objc_msgSend((ID)self.unknown,PTR_s_createFileAtPath_contents_attrib_100eef838,pNVar11,0,0);
  FUN_1000199c0(0,&DAT_100f83ec0,&PTR__OBJC_CLASS___NSFileHandle_100efb9a0);
  (*pcVar19)(lVar17,param_1,UVar9.unknown);
  FUN_100adef1c();
  lVar20 = _TtC10NotesStore17PackageFileWriter::handle;
  if (unaff_x21 == 0) {
    *(long *)(unaff_x20 + _TtC10NotesStore17PackageFileWriter::handle) = lVar17;
    uStack_70 = _UNK_100b825e8;
    local_78.unknown = _DAT_100b825e0;
    local_a4 = 0xdeccbbaa;
    local_c8 = param_1;
    _swift_beginAccess(&local_78,local_a0,0x21,0);
    Foundation::Data::_Representation::append
              ((UnsafeRawBufferPointer)&local_a4,
               (_Representation)((char)&stack0xfffffffffffffff0 + 0x70));
    _swift_endAccess(local_a0);
    uVar15 = uStack_70;
    DVar8.unknown = local_78.unknown;
    self_00 = *(ID *)(unaff_x20 + lVar20);
    FUN_1000266a8(local_78.unknown,uStack_70);
    pNVar12 = Foundation::Data::_bridgeToObjectiveC(DVar8);
    FUN_100026668(DVar8.unknown,uVar15);
    _objc_msgSend(self_00,PTR_s_writeData__100ef6e58,pNVar12);
    uVar6 = (uint)(uStack_70 >> 0x20);
    uVar16 = uVar6 >> 0x1e;
    if (uVar6 >> 0x1e < 2) {
      if (uVar16 == 0) {
        uVar15 = uStack_70 >> 0x30 & 0xff;
      }
      else {
        iVar14 = (int)((ulong)local_78.unknown >> 0x20);
        if (SBORROW4(iVar14,(int)local_78.unknown)) {
                    /* WARNING: Does not return */
          pcVar19 = (code *)SoftwareBreakpoint(1,0x100ae2698);
          (*pcVar19)();
        }
        uVar15 = (ulong)(iVar14 - (int)local_78.unknown);
      }
    }
    else {
      uVar15 = 0;
      if ((uVar16 == 2) &&
         (uVar15 = *(long *)(local_78.unknown + 0x18) - *(long *)(local_78.unknown + 0x10),
         SBORROW8(*(long *)(local_78.unknown + 0x18),*(long *)(local_78.unknown + 0x10)))) {
                    /* WARNING: Does not return */
        pcVar19 = (code *)SoftwareBreakpoint(1,0x100ae24cc);
        (*pcVar19)();
      }
    }
    if (SCARRY8(*(long *)(unaff_x20 + local_d0),uVar15)) {
                    /* WARNING: Does not return */
      pcVar19 = (code *)SoftwareBreakpoint(1,0x100ae2628);
      (*pcVar19)();
    }
    *(ulong *)(unaff_x20 + local_d0) = *(long *)(unaff_x20 + local_d0) + uVar15;
    puVar13 = param_2;
    _swift_bridgeObjectRetain();
    FUN_1008fc11c();
    local_a0[0].unknown = puVar13;
    FUN_1009da240(local_a0,FUN_1007f5424,FUN_100a2bfa0,FUN_100ae4478,FUN_100ae5130);
    _swift_bridgeObjectRelease(param_2);
    _Var7.unknown = local_a0[0].unknown;
    if (((long)local_a0[0].unknown < 0) || (((ulong)local_a0[0].unknown >> 0x3e & 1) != 0)) {
      lVar20 = Swift::_CocoaArrayWrapper::get_endIndex(local_a0[0]);
    }
    else {
      lVar20 = *(long *)(local_a0[0].unknown + 0x10);
    }
    if (lVar20 != 0) {
      uVar15 = 0;
      do {
        if (((ulong)_Var7.unknown & 0xc000000000000001) == 0) {
          if (*(ulong *)(_Var7.unknown + 0x10) <= uVar15) {
                    /* WARNING: Does not return */
            pcVar19 = (code *)SoftwareBreakpoint(1,0x100ae2624);
            (*pcVar19)();
          }
          uVar21 = *(ulong *)(_Var7.unknown + uVar15 * 8 + 0x20);
          _swift_retain(uVar21);
        }
        else {
          uVar21 = uVar15;
          FUN_10072633c(uVar15,_Var7.unknown);
        }
        if (SCARRY8(uVar15,1)) {
                    /* WARNING: Does not return */
          pcVar19 = (code *)SoftwareBreakpoint(1,0x100ae25ec);
          (*pcVar19)();
        }
        lVar17 = uVar15 + 1;
        FUN_100ae26b0(uVar21);
        _swift_release(uVar21);
        uVar15 = uVar15 + 1;
      } while (lVar17 != lVar20);
    }
    FUN_100026668(local_78.unknown,uStack_70);
    _swift_release(_Var7.unknown);
    (**(code **)(lVar18 + 8))(local_c8,UVar9.unknown);
  }
  else {
    _swift_bridgeObjectRelease(param_2);
    pcVar19 = *(code **)(lVar18 + 8);
    (*pcVar19)(param_1,UVar9.unknown);
    (*pcVar19)(unaff_x20 + local_c8,UVar9.unknown);
    lVar20 = unaff_x20 + _TtC10NotesStore17PackageFileWriter::toc;
    uVar2 = *(undefined8 *)(lVar20 + 8);
    uVar4 = *(undefined8 *)(lVar20 + 0x10);
    uVar3 = *(undefined8 *)(lVar20 + 0x18);
    uVar5 = *(undefined8 *)(lVar20 + 0x20);
    _swift_bridgeObjectRelease(*(undefined8 *)(lVar20 + 0x28));
    _swift_bridgeObjectRelease(uVar5);
    _swift_bridgeObjectRelease(uVar3);
    _swift_bridgeObjectRelease(uVar4);
    _swift_bridgeObjectRelease(uVar2);
    FUN_100ae5a5c(0);
    _swift_deallocPartialClassInstance();
  }
  if (*(long *)PTR____stack_chk_guard_100ddc7d0 == local_68) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

