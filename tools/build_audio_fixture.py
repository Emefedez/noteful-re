#!/usr/bin/env python3
"""Synthetic WAV resource fixture. Not exported by Noteful; no sync claim."""
from pathlib import Path
import io,math,struct,sys,wave,json,hashlib
sys.path.insert(0,str(Path(__file__).resolve().parent))
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]/"research/python"))
from noteful import parse,encode_fields,MAGIC
ROOT=Path(__file__).resolve().parents[1]
source=(ROOT/'samples/nota_vacia.noteful').read_bytes();p=parse(source)
wav=io.BytesIO()
with wave.open(wav,'wb') as f:
 f.setnchannels(1);f.setsampwidth(2);f.setframerate(16000)
 f.writeframes(b''.join(struct.pack('<h',int(1000*math.sin(2*math.pi*440*i/16000))) for i in range(4000)))
audio=wav.getvalue();offset=p['index_offset'];body=source[:offset]+audio
fields=p['index_fields'];by_tag={f['tag']:f for f in fields}
for tag,value in [(3,'synthetic-audio'),(10,'synthetic-audio'),(11,offset),(12,len(audio))]:by_tag[tag]['value'].append(value)
index=encode_fields(fields);out=body+index+MAGIC+struct.pack('>QI',len(body),len(index))
dest=ROOT/'tests/fixtures/audio-synthetic.noteful';dest.write_bytes(out)
(ROOT/'research/evidence/audio-synthetic.json').write_text(json.dumps({'fixture':str(dest.relative_to(ROOT)),'synthetic':True,'source':'nota_vacia.noteful with a generated 0.25 second WAV resource','sha256':hashlib.sha256(out).hexdigest(),'audio_bytes':len(audio),'synchronization':'none; not a Noteful recording example'},indent=2)+'\n')
print(dest)
