import sys, unittest
from pathlib import Path
from xml.etree import ElementTree as ET
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'research/python'))
from noteful import parse,semantic_summary,values
from rich_text import decode_rich_text,text_svg
from render_note import render
class TextTests(unittest.TestCase):
 def test_real_text_content_and_fonts(self):
  data=(ROOT/'samples/texto.noteful').read_bytes();summary=semantic_summary(parse(data));runs=[]
  for o in summary['objects']:
   self.assertEqual(o['kind_in_samples'],'rich_text');t=decode_rich_text(values(values(o['payload_fields'])[4]));self.assertEqual(t['warnings'],[]);runs.extend(t['runs'])
  by_text={r['text']:r for r in runs}
  for text,family,size,bold,italic in [('texto texto ','Helvetica',16,False,False),('Bocadillo','Gill Sans',16,True,False),('Hola','Galvji',12,False,True)]:
   r=by_text[text];self.assertEqual(r['font_family'],family);self.assertAlmostEqual(r['font_size']*6/11,size);self.assertEqual(r['bold'],bold);self.assertEqual(r['italic'],italic)
  doc=render(data);self.assertEqual(doc['pages'][0]['warnings'],[]);root=ET.fromstring(doc['pages'][0]['svg']);text=''.join(root.itertext());self.assertIn('Bocadillo',text);self.assertIn('texto texto',text);self.assertIn('Hola',text)
 def test_decorations_and_inheritance(self):
  t=decode_rich_text({2:['uno','dos','tres'],3:[4,0,2],4:[2,3,4,5,4,5],5:[],6:[1,1],7:[],8:[1,1,0,0],9:[],10:[]})
  self.assertEqual(t['warnings'],[]);self.assertTrue(t['runs'][1]['bold']);self.assertEqual(t['runs'][1]['underline'],1);self.assertEqual(t['runs'][2]['underline'],0)
  self.assertIn('underline line-through',text_svg(t,200))
 def test_markup_and_unknown_attributes_keep_characters(self):
  t=decode_rich_text({2:['<script>&\r\nHola'],3:[1],4:[999]});self.assertTrue(t['warnings']);svg=text_svg(t,200);root=ET.fromstring('<svg>'+svg+'</svg>');self.assertEqual(''.join(root.itertext()),'<script>&Hola');self.assertEqual(svg.count('<text '),2)
