#!/usr/bin/env python3
"""Synthetic two-recording regression, derived from the provided Practice note.

Move only stroke 3 twenty seconds later; duplicate the audio under a new asset ID.
This is a parser/UI fixture, NOT evidence of a native multiple-recording export.
"""
from pathlib import Path
import copy, struct, sys
sys.path.insert(0,str(Path(__file__).resolve().parent))
from noteful import parse,encode_fields,MAGIC
ROOT=Path(__file__).resolve().parents[1]
def build():
 source=(ROOT/'samples/Practice book (vol. 1).noteful').read_bytes();report=parse(source)
 blocks={b['id']:source[b['offset']:b['offset']+b['size']] for b in report['blocks']}
 drawing=next(b for b in report['blocks'] if b['kind']=='drawing_metadata')
 fields=copy.deepcopy(drawing['fields']);collection=next(f['value'] for f in fields if f['tag']==7);c={f['tag']:f for f in collection}
 rec=copy.deepcopy(c[0]['value'][0]);r={f['tag']:f for f in rec}
 original_asset=r[3]['value'];new_asset='synthetic-second-audio';new_record='synthetic-second-recording'
 r[1]['value']=new_record;r[2]['value']='Segunda grabación (sintética)';r[3]['value']=r[4]['value']=new_asset;r[5]['value']+=20_000_000
 c[0]['value'].append(rec);c[1]['value'].append(new_record);c[2]['value'].append(c[2]['value'][0]+20_000_000);c[3]['value'].append(1)
 blocks[drawing['id']]=encode_fields(fields)
 editable=next(b for b in report['blocks'] if b['kind']=='stroke_object_set')
 payload=next(f['value'] for f in editable['fields'] if f['tag']==2)
 third=editable['strokes'][2]['offset_in_blob']+payload['offset']-editable['offset']
 raw=bytearray(blocks[editable['id']])
 for offset in (12,20):
  i=third+offset;raw[i:i+8]=(int.from_bytes(raw[i:i+8],'big')+20_000_000).to_bytes(8,'big')
 blocks[editable['id']]=bytes(raw);blocks[new_asset]=blocks[original_asset]
 index=copy.deepcopy(report['index_fields']);idx={f['tag']:f for f in index};idx[3]['value'].append(new_asset)
 body=bytearray(MAGIC);ids=[];offsets=[];sizes=[]
 for key,raw in blocks.items():ids.append(key);offsets.append(len(body));sizes.append(len(raw));body.extend(raw)
 for tag,items in [(10,ids),(11,offsets),(12,sizes)]:idx[tag]['value']=items
 encoded=encode_fields(index);return bytes(body)+encoded+MAGIC+struct.pack('>QI',len(body),len(encoded))
if __name__=='__main__':
 dest=ROOT/'tests/fixtures/multi-audio-synthetic.noteful';dest.write_bytes(build());print(dest)
